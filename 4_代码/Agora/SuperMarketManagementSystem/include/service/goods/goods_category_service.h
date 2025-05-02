#pragma once
#include <crow.h>
#include <string>

class GoodsCategoryService {
public:
  static crow::response create(const std::string &body);
  static crow::response getByGoodsCategoryId(const std::string &body);
  static crow::response updateByGoodsCategoryId(const std::string &body);
  static crow::response removeByGoodsCategoryId(const std::string &body);
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();
};
