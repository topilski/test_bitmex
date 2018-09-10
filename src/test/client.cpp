#include "client.h"

#include <thread>

#include <json-c/json.h>

#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>

#include <common/convert2string.h>
#include <common/macros.h>
#include <common/sprintf.h>
#include <common/time.h>

#include "OrderApi.h"

#define TABLE "table"
#define ACTION "action"
#define DATA "data"
#define KEYS "keys"

#define ACTION_PARTIAL "partial"
#define ACTION_INSERT "insert"
#define ACTION_UPDATE "update"
#define ACTION_DELETE "delete"

#define COMPARE_ACTION(AC, EQ) strcmp(AC, EQ) == 0

#define BASE_URL_REST_API "https://www.bitmex.com/api/v1"
#define ORDER_PATH "/api/v1/order"

static const float kQuantity = 10.0;

namespace {
std::string gen_signature(const std::string& message, const std::string& secret) {
  unsigned char hash_sha256[SHA256_DIGEST_LENGTH];
  unsigned int len;

  HMAC_CTX* ctx = HMAC_CTX_new();
  /* HMAC-SHA256 digest */
  HMAC_Init_ex(ctx, secret.c_str(), secret.length(), EVP_sha256(), 0);
  HMAC_Update(ctx, (unsigned char*)message.c_str(), message.length());
  HMAC_Final(ctx, hash_sha256, &len);
  HMAC_CTX_free(ctx);
  char hash_sha256_hex[SHA256_DIGEST_LENGTH * 2 + 1];
  memset(hash_sha256_hex, 0, SHA256_DIGEST_LENGTH * 2 + 1);

  char* p = &hash_sha256_hex[0];
  unsigned char* h = &hash_sha256[0];
  for (unsigned int i = 0; i < len; ++i, ++h) {
    p += snprintf(p, 3, "%02x", *h);
  }

  return hash_sha256_hex;
}

bool parse_data(json_object* obj, data_array_t* out) {
  json_object* jdata = NULL;
  bool jdata_exist = json_object_object_get_ex(obj, DATA, &jdata);
  if (!jdata_exist) {
    return false;
  }

  array_list* jarray_obj = json_object_get_array(jdata);
  if (!jarray_obj) {
    return false;
  }

  data_array_t dt;
  size_t len = json_object_array_length(jdata);
  if (len == 0) {
    return false;
  }

  for (size_t i = 0; i < len; ++i) {
    json_object* jdata_item = json_object_array_get_idx(jdata, i);
    if (!jdata_item) {
      return false;
    }

    data d;
    if (!make_data(jdata_item, &d)) {
      return false;
    }
    dt.push_back(d);
  }

  DCHECK(!dt.empty());
  *out = dt;
  return true;
}

}  // namespace

Client::Client(const web::websockets::client::websocket_client_config& cfg,
               const std::string& symbol,
               ClientObserver* observer)
    : data_mutex_(), data_(), symbol_(symbol), ws_(cfg), observer_(observer), stop_(false) {}

Client::~Client() {}

data_array_t Client::GetData(const std::string& key) {
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);
  auto it = data_.find(key);
  if (it == data_.end()) {
    return data_array_t();
  }

  return it->second;
}

bool Client::GetLastData(const std::string& key, data* out) {
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);
  auto it = data_.find(key);
  if (it == data_.end()) {
    return false;
  }

  if (it->second.empty()) {
    return false;
  }

  data d = it->second.back();
  *out = d;
  return true;
}

void Client::ClearData(const std::string& key) {
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);
  auto it = data_.find(key);
  if (it == data_.end()) {
    return;
  }

  if (it->second.empty()) {
    return;
  }
  it->second.clear();
}

const std::string& Client::GetSymbol() const {
  return symbol_;
}

void Client::DoOffer(const std::string& public_key,
                     const std::string& secret_key,
                     const data& dt,
                     const std::string& side,
                     common::time64_t nonce) {
  if (dt.symbol != symbol_) {
    NOTREACHED();
  }

  try {
    std::shared_ptr<io::swagger::client::api::ApiConfiguration> conf(new io::swagger::client::api::ApiConfiguration);
    conf->setBaseUrl(BASE_URL_REST_API);
    conf->setApiKey("api-key", public_key);
    std::string cur_time_str = common::ConvertToString(nonce);
    conf->setApiKey("api-nonce", cur_time_str);
    std::string data_str = common::MemSPrintf(
        "{\"ordType\":\"Market\",\"orderQty\":\"%.6f\",\"side\":\"%s\",\"symbol\":\"%s\"}", kQuantity, side, dt.symbol);
    std::string message = "POST" + std::string(ORDER_PATH) + cur_time_str + data_str;

    /*verb = 'POST'
    path = '/api/v1/order'
    expires = 1518064238 # 2018-02-08T04:30:38Z
    data = '{"symbol":"XBTM15","price":219.0,"clOrdID":"mm_bitmex_1a/oemUeQ4CAJZgP3fjHsA","orderQty":98}'

    # HEX(HMAC_SHA256(apiSecret,
    'POST/api/v1/order1518064238{"symbol":"XBTM15","price":219.0,"clOrdID":"mm_bitmex_1a/oemUeQ4CAJZgP3fjHsA","orderQty":98}'))
    # Result is:
    # '1749cd2ccae4aa49048ae09f0b95110cee706e0944e6a14ad0b3a8cb45bd336b'
    signature = HEX(HMAC_SHA256(apiSecret, verb + path + str(expires) + data))*/

    std::string signature = gen_signature(message, secret_key);
    conf->setApiKey("api-signature", signature);
    web::http::client::http_client_config hconf;
    hconf.set_validate_certificates(false);
    conf->setHttpConfig(hconf);
    std::shared_ptr<io::swagger::client::api::ApiClient> cl(new io::swagger::client::api::ApiClient(conf));
    io::swagger::client::api::OrderApi order(cl);
    auto task = order.order_new(
        dt.symbol, side, boost::optional<double>(), kQuantity, boost::optional<double>(), boost::optional<double>(),
        boost::optional<double>(), boost::optional<utility::string_t>(), boost::optional<utility::string_t>(),
        boost::optional<double>(), boost::optional<utility::string_t>(), utility::string_t("Market"),
        boost::optional<utility::string_t>(), boost::optional<utility::string_t>(),
        boost::optional<utility::string_t>(), boost::optional<utility::string_t>());
    auto than_task = task.then([dt, nonce](std::shared_ptr<io::swagger::client::api::Order> ord) {
      common::time64_t answ_time = common::time::current_utc_mstime();
      auto ts = ord->getTimestamp();
      auto str = ts.to_string(utility::datetime::ISO_8601);
      common::time64_t resp_time;
      if (make_timestamp(str, &resp_time)) {
        auto diff = resp_time - dt.timestamp;
        auto ldiff = answ_time - nonce;
        INFO_LOG() << "symbol: " << dt.symbol << ", nonce: " << nonce << " exec: " << diff << ", latency: " << ldiff;
      }
    });
    than_task.wait();
  } catch (const io::swagger::client::api::ApiException& aex) {
    auto ct = aex.getContent();
    char ch[256];
    ct->getline(ch, 256);
    WARNING_LOG() << "rest error: " << ch;
  } catch (const web::websockets::client::websocket_exception& e) {
    WARNING_LOG() << "rest error: " << e.what();
  }
}

void Client::Stop() {
  stop_ = true;
}

void Client::Run() {
  auto uri = make_uri(symbol_);
  try {
    auto conn_task = ws_.connect(uri);
    conn_task.wait();
    while (!stop_) {
      auto recv = ws_.receive();
      auto msg = recv.then(
          [](const web::websockets::client::websocket_incoming_message& in_msg) { return in_msg.extract_string(); });
      auto msg2 = msg.then([this](const std::string& msg) {
        if (msg.empty()) {
          return;
        }

        // INFO_LOG() << msg;
        const char* msg_ptr = msg.c_str();
        json_object* parsed = json_tokener_parse(msg_ptr);
        if (!parsed) {
          return;
        }

        json_object* jaction = NULL;
        bool jjaction_exist = json_object_object_get_ex(parsed, ACTION, &jaction);
        if (!jjaction_exist) {
          json_object_put(parsed);
          return;
        }

        handle_action(json_object_get_string(jaction), parsed);
        json_object_put(parsed);
      });
      msg2.wait();
    }

  } catch (const web::websockets::client::websocket_exception& e) {
    WARNING_LOG() << "websocket error: " << e.what();
  }
  ws_.close();

  if (observer_) {
    observer_->Finished();
  }
}

web::uri Client::make_uri(const std::string& symbol) {
  static const std::string symbolSubs[] = {QUOTE};
  std::string query;
  for (size_t i = 0; i < SIZEOFMASS(symbolSubs); ++i) {
    query += symbolSubs[i] + ":" + symbol;
    if (i != SIZEOFMASS(symbolSubs) - 1) {
      query += ",";
    }
  }
  // wss://www.bitmex.com/realtime?subscribe=quote:XBTU18,trade:XBTU18
  return "wss://www.bitmex.com/realtime?subscribe=" + query;
}

void Client::Update(const std::string& key) {
  if (observer_) {
    observer_->Notify(this, key);
  }
}

void Client::handle_action(const char* action, json_object* obj) {
  json_object* jtable = NULL;
  bool jtable_exist = json_object_object_get_ex(obj, TABLE, &jtable);
  if (!jtable_exist) {
    return;
  }

  const char* key = json_object_get_string(jtable);
  if (COMPARE_ACTION(action, ACTION_PARTIAL)) {
    /*{"table":"quote","action":"partial","keys":[],"types":{"timestamp":"timestamp","symbol":"symbol","bidSize":"long","bidPrice":"float","askPrice":"float","askSize":"long"},"foreignKeys":{"symbol":"instrument"},"attributes":{"timestamp":"sorted","symbol":"grouped"},"filter":{"symbol":"XBTU18"},"data":[{"timestamp":"2018-09-04T17:34:10.448Z","symbol":"XBTU18","bidSize":5435,"bidPrice":7367.5,"askPrice":7368,"askSize":184546}]}*/

    data_array_t dt;
    if (parse_data(obj, &dt)) {
      std::lock_guard<std::recursive_mutex> lock(data_mutex_);
      data_[key] = dt;
      Update(key);
    }
  } else if (COMPARE_ACTION(action, ACTION_INSERT)) {
    data_array_t dt;
    if (parse_data(obj, &dt)) {
      std::lock_guard<std::recursive_mutex> lock(data_mutex_);
      data_[key] = dt;
      Update(key);
    }
  } else if (COMPARE_ACTION(action, ACTION_UPDATE)) {
    data_array_t dt;
    if (parse_data(obj, &dt)) {
      Update(key);
    }
  } else if (COMPARE_ACTION(action, ACTION_DELETE)) {
    data_array_t dt;
    if (parse_data(obj, &dt)) {
      Update(key);
    }
  }
}
