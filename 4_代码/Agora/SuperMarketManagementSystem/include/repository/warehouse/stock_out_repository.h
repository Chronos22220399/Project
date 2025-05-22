#pragma once
#include <model/dto/warehouse/stock_out_dto.hpp>
#include <common/generic_model.hpp>

class StockOutRepository : public model::GenericModel<StockOutDTO, db::stock_out> {
public:
    // CRUD Operations
    static insert_ret_type create(const StockOutDTO& StockOutDTO);
    static select_ret_type<StockOutDTO> get(const std::string &stock_out_name);
    static update_ret_type update(const StockOutDTO& stock_out_dto);
    static delete_ret_type remove(const std::string &stock_out_id);
    
    // Custom Queries
    static select_ret_type<StockOutDTO> getAll();
    static select_ret_type<StockOutDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
