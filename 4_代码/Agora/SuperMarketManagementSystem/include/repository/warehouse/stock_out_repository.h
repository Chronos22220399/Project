#pragma once
#include <common/generic_model.hpp>
#include <model/dto/warehouse/stock_out_dto.hpp>

class StockOutRepository
  : public model::GenericModel<StockOutDTO, db::stock_out> {
  public:
  // CRUD Operations
  static insert_ret_type create(const StockOutDTO& StockOutDTO);
  static update_ret_type updateById(const in_id_type id,
                                    const StockOutDTO& stock_out_dto);
  static delete_ret_type removeById(const in_id_type id);

  // Custom Queries
  static select_ret_type<StockOutDTO> getAll();
  static select_ret_type<StockOutDTO> getByPage(int page_size, int offset);
  static count_type count();


  static in_id_type getInternalId(const std::string& stock_out_id);
  static ex_id_type getExternalId(in_id_type id);

  // 其他方法实现...
  // Foreign Key Relations
};
