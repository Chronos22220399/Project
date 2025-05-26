#pragma once
#include <common/generic_model.hpp>
#include <model/dto/sales/sales_order_dto.hpp>

class SalesOrderRepository
  : public model::GenericModel<SalesOrderDTO, db::sales_order> {
  public:
  // CRUD Operations
  static insert_ret_type create(const SalesOrderDTO& SalesOrderDTO);
  static select_ret_type<SalesOrderDTO>
  get(const std::string& sales_order_name);
  static update_ret_type updateById(const SalesOrderDTO& sales_order_dto);
  static delete_ret_type removeById(const in_id_type id);

  // Custom Queries
  static select_ret_type<SalesOrderDTO> getAll();
  static select_ret_type<SalesOrderDTO> getByPage(int page_size, int offset);
  static count_type count();


  // Foreign Key Relations
};
