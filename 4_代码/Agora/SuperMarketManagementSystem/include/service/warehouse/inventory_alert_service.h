#pragma once
#include <crow.h>
#include <string>

class InventoryAlertService {
public:
  static crow::response create(const std::string &body);
  static crow::response update(const std::string &body);
  static crow::response remove(const std::string &body);
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();
};
