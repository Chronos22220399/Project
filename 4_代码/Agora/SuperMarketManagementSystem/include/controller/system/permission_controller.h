#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class PermissionController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
