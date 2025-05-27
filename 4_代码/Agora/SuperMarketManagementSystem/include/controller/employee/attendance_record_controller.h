#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class AttendanceRecordController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
