#pragma once

#include <string>

#include <common/types.h>

struct data {
  double ask_price;
  int ask_size;
  int bid_price;
  int bid_size;
  std::string symbol;
  common::time64_t timestamp;
};

bool make_timestamp(std::string timestamp, common::time64_t* time);
bool make_data(struct json_object* obj, data* out);
