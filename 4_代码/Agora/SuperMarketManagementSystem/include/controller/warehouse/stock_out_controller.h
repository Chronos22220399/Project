#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class StockOutController {
  public:
  static void registerRoutes(crow::SimpleApp& app);
};
