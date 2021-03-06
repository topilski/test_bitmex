#pragma once

#include <cpprest/ws_client.h>

#include <common/macros.h>

#include <memory>

#include "data.h"

#define QUOTE "quote"
#define TRADE "trade"

#define SIDE_TYPE_BUY "Buy"
#define SIDE_TYPE_SELL "Sell"

typedef std::shared_ptr<data> data_t;

class Client {
 public:
  class ClientObserver {
   public:
    virtual void Notify(Client* client, const std::string& key) = 0;
    virtual void Finished() = 0;
  };

  Client(const web::websockets::client::websocket_client_config& cfg,
         const std::string& symbol,
         ClientObserver* observer);

  ~Client();

  data_t GetLastData() const;
  void ClearData();

  void Run();
  void Stop();

  const std::string& GetSymbol() const;

  bool DoOffer(const std::string& public_key,
               const std::string& secret_key,
               data_t dt,
               const std::string& side,
               common::time64_t nonce);

 private:
  static web::uri make_uri(const std::string& symbol);
  void handle_action(const char* action, struct json_object* obj);
  void Update(const std::string& key);

  DISALLOW_COPY_AND_ASSIGN(Client);
  data_t last_data_;
  const std::string symbol_;
  web::websockets::client::websocket_client ws_;
  ClientObserver* observer_;

  bool stop_;
};
