#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class PointsPolicyController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
