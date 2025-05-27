#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class RoleController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
