#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class PositionController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
