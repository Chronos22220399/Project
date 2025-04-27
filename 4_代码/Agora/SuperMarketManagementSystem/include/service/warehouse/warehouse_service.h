#pragma once
#include <crow.h>
#include <string>

class WarehouseService {
public:
  static crow::response add(const std::string &body);
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();
};
