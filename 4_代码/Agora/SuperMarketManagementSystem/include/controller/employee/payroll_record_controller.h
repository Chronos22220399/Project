#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class PayrollRecordController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
