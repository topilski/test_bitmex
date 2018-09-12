#include <future>
#include <thread>

#include "client.h"

#define XBTUSD "XBTUSD"
#define XBTU18 "XBTU18"

#define DIFF_1 50

#define DIFF_2 40

#define RETRY_COUNT 5
#define NONCE_DIFF 1

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
          common::time64_t nonce = std::max(xbtusd_data->timestamp, xbtu18_data->timestamp);
          auto cb1 = [this, xbtusd_data](common::time64_t nonce) {
            return xbtusd_client_->DoOffer(public_key_, secret_key_, xbtusd_data, SIDE_TYPE_SELL, nonce);
          };
          auto cb2 = [this, xbtu18_data](common::time64_t nonce) {
            return xbtu18_client_->DoOffer(public_key_, secret_key_, xbtu18_data, SIDE_TYPE_BUY, nonce);
          };
          std::future<bool> th1 = std::async(std::launch::async, cb1, nonce);
          std::future<bool> th2 = std::async(std::launch::async, cb2, nonce + NONCE_DIFF);
          xbtusd_client_->ClearData();
          xbtu18_client_->ClearData();
          th1.wait();
          th2.wait();
          bool result = th1.get();
          result &= th2.get();
          if (result) {
            reverse_ = 2;
          } else {
            usleep(500000);
          }
          INFO_LOG() << "diff: " << diff << ", reverse: " << reverse_ << ", result: " << result;
          return;
        }
      }

      if (reverse_ != 1) {
        int diff = xbtusd_data->ask_price - xbtu18_data->bid_price;
        if (diff <= DIFF_2) {
          common::time64_t nonce = std::max(xbtusd_data->timestamp, xbtu18_data->timestamp);
          auto cb1 = [this, xbtusd_data](common::time64_t nonce) {
            return xbtusd_client_->DoOffer(public_key_, secret_key_, xbtusd_data, SIDE_TYPE_BUY, nonce);
          };
          auto cb2 = [this, xbtu18_data](common::time64_t nonce) {
            return xbtu18_client_->DoOffer(public_key_, secret_key_, xbtu18_data, SIDE_TYPE_SELL, nonce);
          };
          xbtusd_client_->ClearData();
          xbtu18_client_->ClearData();
          std::future<bool> th1 = std::async(std::launch::async, cb1, nonce);
          std::future<bool> th2 = std::async(std::launch::async, cb2, nonce + NONCE_DIFF);
          xbtusd_client_->ClearData();
          xbtu18_client_->ClearData();
          th1.wait();
          th2.wait();
          bool result = th1.get();
          result &= th2.get();
          if (result) {
            reverse_ = 1;
          } else {
            usleep(500000);
          }
          INFO_LOG() << "diff: " << diff << ", reverse: " << reverse_ << ", result: " << result;
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
