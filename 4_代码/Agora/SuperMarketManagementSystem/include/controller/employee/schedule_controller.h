#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class ScheduleController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
