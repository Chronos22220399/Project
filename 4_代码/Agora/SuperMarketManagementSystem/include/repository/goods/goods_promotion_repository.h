#pragma once
#include <model/dto/goods/goods_promotion_dto.hpp>
#include <common/generic_model.hpp>

class GoodsPromotionRepository : protected model::GenericModel<GoodsPromotionDTO, db::goods_promotion> {
public:
    // CRUD Operations
    static insert_ret_type create(const GoodsPromotionDTO& GoodsPromotionDTO);
    static select_ret_type<GoodsPromotionDTO> get(id_type id);
    static update_ret_type update(const GoodsPromotionDTO& goods_promotion_dto);
    static delete_ret_type remove(id_type id);
    
    // Custom Queries
    static select_ret_type<GoodsPromotionDTO> getAll();
    static select_ret_type<GoodsPromotionDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    // Foreign Key Relations
    static select_ret_type<GoodsPromotionDTO> getByGoodsId(id_type goods_id);
    static select_ret_type<GoodsPromotionDTO> getByPromotionId(id_type promotion_id);
};
