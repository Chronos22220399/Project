#include <repository/goods/goods_promotion_repository.h>


// 面向业务 CRUD（external）
select_ret_type<GoodsPromotionDTO>
GoodsPromotionRepository::getByGoodsRKId(in_id_type goods_rk_id)
{
  return _select(db::goods_promotion{}.goods_rk_id == goods_rk_id);
}

select_ret_type<GoodsPromotionDTO>
GoodsPromotionRepository::getByPromotionRKId(in_id_type promotion_rk_id)
{
  return _select(db::goods_promotion{}.promotion_rk_id == promotion_rk_id);
}

update_ret_type GoodsPromotionRepository::updateByGoodsRKId(
  in_id_type goods_rk_id, const GoodsPromotionDTO& goods_promotion_dto)
{
  return _update(goods_promotion_dto,
                 db::goods_promotion{}.goods_rk_id == goods_rk_id);
}

delete_ret_type
GoodsPromotionRepository::removeByGoodRKsId(in_id_type goods_rk_id)
{
  return _remove(db::goods_promotion{}.goods_rk_id == goods_rk_id);
}

bool GoodsPromotionRepository::existsByGoodsRKId(in_id_type goods_rk_id)
{
  return _exists(db::goods_promotion{}.goods_rk_id == goods_rk_id);
}
