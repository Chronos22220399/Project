#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class MemberPurchaseRecordController {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
