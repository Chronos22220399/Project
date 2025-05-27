#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class SystemUpdateLogController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
