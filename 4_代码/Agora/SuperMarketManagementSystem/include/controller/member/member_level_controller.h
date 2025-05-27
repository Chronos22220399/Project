#pragma once
#include <crow.h>
#include <model/dto/member/member_level_dto.hpp>
#include <nlohmann/json.hpp>

class MemberLevelController {
  public:
  static void registerRoutes(crow::SimpleApp& app);
};
