#pragma once
#include <common/common_utils.hpp>
#include <controller/sales/sales_order_controller.h>
#include <crow.h>
#include <nlohmann/json.hpp>

class SalesOrderController {
  public:
  static void registerRoutes(crow::SimpleApp& app);
};
