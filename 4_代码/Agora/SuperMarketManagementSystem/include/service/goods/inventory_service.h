#pragma once
#include <crow.h>
#include <string>

class InventoryService {
public:
  static crow::response add(const std::string &body);
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();
  static crow::response getByGoodsId(const std::string &body);
};
