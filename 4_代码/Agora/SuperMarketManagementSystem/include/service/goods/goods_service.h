#pragma once
#include <crow.h>
#include <string>

class GoodsService {
public:
  static crow::response create(const std::string &body);
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();

  // 获取详细商品信息
  static crow::response getGoodsDetailInfoById(const std::string &body);
};
