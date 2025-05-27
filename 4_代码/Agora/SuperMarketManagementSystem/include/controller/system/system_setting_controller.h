#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class SystemSettingController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
