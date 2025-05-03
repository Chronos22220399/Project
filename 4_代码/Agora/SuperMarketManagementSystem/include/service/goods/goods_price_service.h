#pragma once
#include <crow.h>
#include <string>

class GoodsPriceService {
public:
  // Not implemented
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();

  // Implemented
  static crow::response create(const std::string &body);

  static crow::response updateByGoodsId(const std::string &body);

  static crow::response removeByGoodsId(const std::string &body);
};
