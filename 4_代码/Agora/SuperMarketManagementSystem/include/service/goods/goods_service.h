#pragma once
#include <crow.h>
#include <string>

class GoodsService {
public:
  static crow::response addGoods(const std::string &body);
  static crow::response getGoodsByPage(const std::string &body);
  static crow::response getAllGoods();
};
