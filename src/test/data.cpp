#include "data.h"

#include <string.h>

#include <json-c/json.h>

#include <common/macros.h>
#include <common/time.h>
#include <common/convert2string.h>

#define DATA_ASK_PRICE "askPrice"
#define DATA_ASK_SIZE "askSize"
#define DATA_BID_PRICE "bidPrice"
#define DATA_BID_SIZE "bidSize"
#define DATA_SYMBOL "symbol"
#define DATA_TIMESTAMP "timestamp"

bool make_timestamp(std::string timestamp, common::time64_t* time) {
  uint16_t frac = 0;
  std::size_t found = timestamp.find_last_of('.');
  if (found != std::string::npos) {
    std::string last_part = timestamp.substr(found + 1);
    if (last_part.back() == 'Z') {
      last_part.pop_back();
    }
    common::ConvertFromString(last_part, &frac);
    timestamp.resize(found);
  }

  struct tm tm;
  memset(&tm, 0, sizeof(struct tm));
  char* res = strptime(timestamp.c_str(), "%Y-%m-%dT%H:%M:%S", &tm);
  if (!res) {
    return false;
  }

  *time = common::time::tm2utctime(&tm) * 1000;
  *time += frac;
  return true;
}
bool make_data(json_object* obj, data* out) {
  data d;
  json_object* jask_price = NULL;
  bool jask_price_exist = json_object_object_get_ex(obj, DATA_ASK_PRICE, &jask_price);
  if (!jask_price_exist) {
    return false;
  }

  json_object* jask_size = NULL;
  bool jask_size_exist = json_object_object_get_ex(obj, DATA_ASK_SIZE, &jask_size);
  if (!jask_size_exist) {
    return false;
  }

  json_object* jbid_price = NULL;
  bool jbid_price_exist = json_object_object_get_ex(obj, DATA_BID_PRICE, &jbid_price);
  if (!jbid_price_exist) {
    return false;
  }

  json_object* jbid_size = NULL;
  bool jbid_size_exist = json_object_object_get_ex(obj, DATA_BID_SIZE, &jbid_size);
  if (!jbid_size_exist) {
    return false;
  }

  json_object* jsymbol = NULL;
  bool jsymbol_exist = json_object_object_get_ex(obj, DATA_SYMBOL, &jsymbol);
  if (!jsymbol_exist) {
    return false;
  }

  json_object* jtimestamp = NULL;
  bool jtimestamp_exist = json_object_object_get_ex(obj, DATA_TIMESTAMP, &jtimestamp);
  if (!jtimestamp_exist) {
    return false;
  }

  common::time64_t ts;
  if (!make_timestamp(json_object_get_string(jtimestamp), &ts)) {
    DNOTREACHED();
    return false;
  }
  d.ask_price = json_object_get_double(jask_price);
  d.ask_size = json_object_get_int(jask_size);
  d.bid_price = json_object_get_int(jbid_price);
  d.bid_size = json_object_get_int(jbid_size);
  d.symbol = json_object_get_string(jsymbol);
  d.timestamp = ts;  // utc timestamp
  *out = d;
  return true;
}
