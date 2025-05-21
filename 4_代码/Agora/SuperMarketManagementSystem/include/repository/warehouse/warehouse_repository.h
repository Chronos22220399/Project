#pragma once
#include <common/generic_model.hpp>
#include <model/dto/warehouse/warehouse_dto.hpp>

class WarehouseRepository
  : protected model::GenericModel<WarehouseDTO, db::warehouse> {
  public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const WarehouseDTO& warehouse_dto);

  static select_ret_type<WarehouseDTO> getById(in_id_type id);

  static update_ret_type updateById(in_id_type id,
                                    const WarehouseDTO& warehouse_dto);

  static delete_ret_type removeById(in_id_type id);

  static bool existsById(in_id_type id);


  // 面向业务 CRUD（external）
  static select_ret_type<WarehouseDTO>
  getByWarehouseId(const std::string& warehouse_id);

  static select_ret_type<WarehouseDTO>
  getByWarehouseName(const std::string& warehouse_name);

  static select_ret_type<WarehouseDTO>
  getByLocation(const std::string& location);

  static update_ret_type updateByWarehouseId(const std::string& warehouse_id,
                                             const WarehouseDTO& warehouse_dto);

  static delete_ret_type removeByWarehouseId(const std::string& warehouse_id);

  static bool existsByWarehouseId(const std::string& warehouse_id);

  static bool existsByWarehouseName(const std::string& warehouse_name);

  static bool existsByLocation(const std::string& location);

  // other
  static select_ret_type<WarehouseDTO> getAll();

  static select_ret_type<WarehouseDTO> getByPage(count_type page_size,
                                                 count_type offset);

  static count_type count();

  // 获取 id 用于缓存映射
  static in_id_type getInternalId(const std::string& warehouse_id);

  // 获取 external id 用于缓存映射
  static std::string getExternalId(in_id_type id);

  // 设置 status
  static update_ret_type setStatus(const in_id_type id,
                                   const status_type& status);
};
