#include <thread>

#include "client.h"

#include <common/time.h>

#define XBTUSD "XBTUSD"
#define XBTU18 "XBTU18"

#define DIFF 5

#define FREEZE_TIME_MSEC 30000

static const std::string symbols[] = {XBTUSD, XBTU18};

enum { CLIENTS_COUNT = SIZEOFMASS(symbols) };

class HandlerData : public Client::ClientObserver {
 public:
  explicit HandlerData(const std::string& public_key, const std::string& secret_key)
      : xbtusd_client_(nullptr),
        xbtu18_client_(nullptr),
        public_key_(public_key),
        secret_key_(secret_key),
        last_order_time_(0) {}
  virtual ~HandlerData() {}

  virtual void Finished() {
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
    common::time64_t lstime = common::time::current_utc_mstime();
    auto skip_time = lstime - last_order_time_;
    if (skip_time < FREEZE_TIME_MSEC) {
      xbtusd_client_->ClearData(key);
      xbtu18_client_->ClearData(key);
      INFO_LOG() << "skip request: " << skip_time;
      return;
    }

    data xbtu18_data;
    data xbtusd_data;
    if (xbtusd_client_->GetLastData(key, &xbtusd_data) && xbtu18_client_->GetLastData(key, &xbtu18_data)) {
      int diff = xbtusd_data.ask_price - xbtu18_data.bid_price;
      if (diff % DIFF == 0) {
        common::time64_t cur_time = common::time::current_utc_mstime();
        std::thread th1 = std::thread([this, xbtusd_data, cur_time] {
          xbtusd_client_->DoOffer(public_key_, secret_key_, xbtusd_data, SIDE_TYPE_BUY, cur_time);
        });
        std::thread th2 = std::thread([this, xbtu18_data, cur_time] {
          xbtu18_client_->DoOffer(public_key_, secret_key_, xbtu18_data, SIDE_TYPE_SELL, cur_time + 5);
        });
        xbtusd_client_->ClearData(key);
        xbtu18_client_->ClearData(key);
        last_order_time_ = common::time::current_utc_mstime();
        th1.join();
        th2.join();
      }
      INFO_LOG() << "diff: " << diff;
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
  common::time64_t last_order_time_;
};

int main(int argc, char* argv[]) {
  if (argc != 3) {
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
