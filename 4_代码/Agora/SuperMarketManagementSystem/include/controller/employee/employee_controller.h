#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class EmployeeController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
