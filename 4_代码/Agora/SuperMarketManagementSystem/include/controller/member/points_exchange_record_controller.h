#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class PointsExchangeRecordController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
