#pragma once
#include <common/common_utils.hpp>
#include <crow.h>
#include <repository/goods/goods_price_repository.h>
#include <string>

class GoodsPriceService {
  public:
  // Implemented
  static ServiceResult create(const GoodsPriceDTO& gp_dto);

  static ServiceResult removeByGoodsId(const std::string& goods_id);

  static ServiceResult updateByGoodsRKId(const in_id_type goods_id,
                                         const GoodsPriceDTO& gp_dto);

  // Not implemented
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
