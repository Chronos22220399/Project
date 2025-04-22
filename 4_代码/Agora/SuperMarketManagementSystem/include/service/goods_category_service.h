#pragma once
#include <crow.h>
#include <string>

class GoodsCategoryService {
public:
  static crow::response addCategory(const std::string &body);
  static crow::response getCategoryByPage(const std::string &body);
  static crow::response getAllCategory();
};
