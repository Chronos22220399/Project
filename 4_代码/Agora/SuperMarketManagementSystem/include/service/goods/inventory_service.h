#pragma once
#include <crow.h>
#include <string>

class InventoryService {
public:
  static crow::response create(const std::string &body);
  // static crow::response getByGoodRKId(const std::string &body);
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();
};
