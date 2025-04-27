#pragma once
#include <common/generic_model.hpp>
#include <model/dto/goods/inventory_dto.hpp>

class InventoryRepository
    : public model::GenericModel<InventoryDTO, db::inventory> {
public:
  // CRUD Operations
  static insert_ret_type create(const InventoryDTO &InventoryDTO);
  static select_ret_type<InventoryDTO> get(id_type id);
  static update_ret_type update(const InventoryDTO &inventory_dto);
  static delete_ret_type remove(id_type id);

  // Custom Queries
  static select_ret_type<InventoryDTO> getAll();
  static select_ret_type<InventoryDTO> getByPage(int page_size, int offset);
  static count_type count();

  // Foreign Key Relations
  static select_ret_type<InventoryDTO> getByGoodsId(id_type goods_id);
  static select_ret_type<InventoryDTO> getByWarehouseId(id_type warehouse_id);
};
