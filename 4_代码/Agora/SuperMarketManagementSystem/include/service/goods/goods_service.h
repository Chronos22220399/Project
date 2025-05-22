#pragma once
// stl
#include <crow.h>
#include <string>
// third_party
#include <nlohmann/json.hpp>
// model
#include <model/dto/goods/goods_dto.hpp>


class GoodsService {
  public:
  static ServiceResult create(GoodsDTO& goods_dto);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
  static ServiceResult updateByGoodsId(const std::string& goods_id, GoodsDTO& goods_dto);
  static ServiceResult removeByGoodsId(const std::string& goods_id);

  // 获取详细商品信息
  static ServiceResult getGoodsDetailInfoById(const in_id_type id);
};
