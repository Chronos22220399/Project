#pragma once
#include <crow.h>
#include <string>

class PromotionService {
public:
  // Implemented
  static crow::response add(const std::string &body);

  static crow::response removeByPromotionId(const std::string &body);

  static crow::response updateByPromotionId(const std::string &body);

  // Not implemented
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();
};
