#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class SalesReturnController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
