#pragma once
#include <crow.h>
#include <string>

class GoodsPriceService {
public:
  // Not implemented
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();

  // Implemented
  static crow::response add(const std::string &body);

  static crow::response updateByGoodsRKId(const std::string &body);

  static crow::response removeByGoodsRKId(const std::string &body);
};
