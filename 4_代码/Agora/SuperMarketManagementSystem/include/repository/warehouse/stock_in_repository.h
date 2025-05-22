#pragma once
#include <common/generic_model.hpp>
#include <model/dto/warehouse/stock_in_dto.hpp>

class StockInRepository : public model::GenericModel<StockInDTO, db::stock_in> {
  public:
  // CRUD Operations
  static insert_ret_type create(const StockInDTO& StockInDTO);
  static select_ret_type<StockInDTO> get(const in_id_type id);
  static update_ret_type update(const StockInDTO& stock_in_dto);
  static delete_ret_type remove(const std::string& stock_in_id);

  // Custom Queries
  static select_ret_type<StockInDTO> getAll();
  static select_ret_type<StockInDTO> getByPage(int page_size, int offset);
  static count_type count();


  // Foreign Key Relations
};
