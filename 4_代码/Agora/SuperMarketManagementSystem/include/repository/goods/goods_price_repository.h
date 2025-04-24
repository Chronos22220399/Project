#pragma once
#include <model/dto/goods/goods_price_dto.hpp>
#include <common/generic_model.hpp>

class GoodsPriceRepository : protected model::GenericModel<GoodsPriceDTO, db::goods_price> {
public:
    // CRUD Operations
    static insert_ret_type create(const GoodsPriceDTO& GoodsPriceDTO);
    static select_ret_type<GoodsPriceDTO> get(id_type id);
    static update_ret_type update(const GoodsPriceDTO& goods_price_dto);
    static delete_ret_type remove(id_type id);
    
    // Custom Queries
    static select_ret_type<GoodsPriceDTO> getAll();
    static select_ret_type<GoodsPriceDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    // Foreign Key Relations
    static select_ret_type<std::vector<GoodsPriceDTO>> getByGoodsId(id_type goods_id);
};
