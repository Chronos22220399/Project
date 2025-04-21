#pragma once
#include <model/dto/goods_dto.hpp>

class GoodsRepository : public Model::GenericModel<GoodsDTO, db::goods> {
public:
  static bool insert(const GoodsDTO &goods_dto);
};
