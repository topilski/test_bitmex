#include <thread>

#include <iostream>

#include <common/time.h>

#include "client.h"

#define XBTUSD "XBTUSD"
#define XBTU18 "XBTU18"

#define DIFF_1 50

#define DIFF_2 40

// short sell
// long buy

#define FREEZE_TIME_MSEC 30000

#define HELP_TEXT            \
  "Usage: " PROJECT_NAME     \
  " [options]\n"             \
  "  Bitmex " PROJECT_NAME   \
  " project.\n\n"            \
  "    argv[1] public key\n" \
  "    argv[2] private key\n"

static const std::string symbols[] = {XBTUSD, XBTU18};

enum { CLIENTS_COUNT = SIZEOFMASS(symbols) };

class HandlerData : public Client::ClientObserver {
 public:
  explicit HandlerData(const std::string& public_key, const std::string& secret_key)
      : xbtusd_client_(nullptr),
        xbtu18_client_(nullptr),
        public_key_(public_key),
        secret_key_(secret_key),
        reverse_(0) {}
  virtual ~HandlerData() {}

  virtual void Finished() override {
    if (xbtusd_client_) {
      xbtusd_client_->Stop();
    }

    if (xbtu18_client_) {
      xbtu18_client_->Stop();
    }
  }

  virtual void Notify(Client* client, const std::string& key) override {
    UNUSED(client);
    if (key != QUOTE) {
      return;
    }

    if (!xbtusd_client_ || !xbtu18_client_) {
      return;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    data_t xbtu18_data = xbtu18_client_->GetLastData();
    data_t xbtusd_data = xbtusd_client_->GetLastData();
    if (xbtu18_data && xbtusd_data) {
      if (reverse_ != 2) {
        int diff = xbtusd_data->bid_price - xbtu18_data->ask_price;
        if (diff >= DIFF_1) {
          common::time64_t cur_time = common::time::current_utc_mstime();
          common::time64_t max_serv_time = std::max(xbtusd_data->timestamp, xbtu18_data->timestamp);
          common::time64_t nonce = std::max(cur_time, max_serv_time);
          std::thread th1 = std::thread([this, xbtusd_data, nonce] {
            xbtusd_client_->DoOffer(public_key_, secret_key_, xbtusd_data, SIDE_TYPE_SELL, nonce);
          });
          std::thread th2 = std::thread([this, xbtu18_data, nonce] {
            xbtu18_client_->DoOffer(public_key_, secret_key_, xbtu18_data, SIDE_TYPE_BUY, nonce + 5);
          });
          xbtusd_client_->ClearData();
          xbtu18_client_->ClearData();
          reverse_ = 2;
          th1.join();
          th2.join();
          INFO_LOG() << "diff: " << diff << ", reverse: " << reverse_;
          return;
        }
      }

      if (reverse_ != 1) {
        int diff = xbtusd_data->ask_price - xbtu18_data->bid_price;
        if (diff <= DIFF_2) {
          common::time64_t cur_time = common::time::current_utc_mstime();
          common::time64_t max_serv_time = std::max(xbtusd_data->timestamp, xbtu18_data->timestamp);
          common::time64_t nonce = std::max(cur_time, max_serv_time);
          std::thread th1 = std::thread([this, xbtusd_data, nonce] {
            xbtusd_client_->DoOffer(public_key_, secret_key_, xbtusd_data, SIDE_TYPE_BUY, nonce);
          });
          std::thread th2 = std::thread([this, xbtu18_data, nonce] {
            xbtu18_client_->DoOffer(public_key_, secret_key_, xbtu18_data, SIDE_TYPE_SELL, nonce + 5);
          });
          xbtusd_client_->ClearData();
          xbtu18_client_->ClearData();
          reverse_ = 1;
          th1.join();
          th2.join();
          INFO_LOG() << "diff: " << diff << ", reverse: " << reverse_;
          return;
        }
      }

      /*INFO_LOG() << "xbtusd_data.bid_price: " << xbtusd_data.bid_price
                 << ", xbtu18_data.ask_price: " << xbtu18_data.ask_price << ", reverse: " << reverse_;*/
    }
  }

  void RegisterClient(Client* cl) {
    if (cl->GetSymbol() == XBTUSD) {
      xbtusd_client_ = cl;
    } else if (cl->GetSymbol() == XBTU18) {
      xbtu18_client_ = cl;
    } else {
      NOTREACHED();
    }
  }

 private:
  Client* xbtusd_client_;
  Client* xbtu18_client_;

  std::mutex mutex_;
  const std::string public_key_;
  const std::string secret_key_;

  int reverse_;
};

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << HELP_TEXT << std::endl;
    return 1;
  }

  const std::string pub_key = argv[1];
  const std::string priv_key = argv[2];
  common::logging::INIT_LOGGER(PROJECT_NAME, common::logging::LOG_LEVEL_INFO);
  web::websockets::client::websocket_client_config cfg;
  cfg.set_validate_certificates(false);

  HandlerData* handler = new HandlerData(pub_key, priv_key);

  Client* clients[CLIENTS_COUNT];
  std::thread threads[CLIENTS_COUNT];
  for (size_t i = 0; i < CLIENTS_COUNT; ++i) {
    const std::string pair = symbols[i];
    Client* cl = new Client(cfg, pair, handler);
    handler->RegisterClient(cl);
    threads[i] = std::thread([cl]() { cl->Run(); });
    clients[i] = cl;
  }

  for (size_t i = 0; i < CLIENTS_COUNT; ++i) {
    threads[i].join();
    delete clients[i];
  }

  delete handler;
  return 0;
}
