#pragma once
#include <common/generic_model.hpp>
#include <model/dto/goods/inventory_dto.hpp>

class InventoryRepository
    : public model::GenericModel<InventoryDTO, db::inventory> {
public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const InventoryDTO &inventory_dto);
  static select_ret_type<InventoryDTO> getById(id_type id);
  static update_ret_type updateById(id_type id,
                                    const InventoryDTO &inventory_dto);
  static delete_ret_type removeById(id_type id);
  static bool existsById(id_type id);

  // 面向业务 CRUD（external）
  static select_ret_type<InventoryDTO> getByGoodsRKId(id_type goods_rk_id);
  static select_ret_type<InventoryDTO>
  getByWarehouseRKId(id_type warehouse_rk_id);
  static update_ret_type updateByGoodsRKId(id_type goods_rk_id,
                                           const InventoryDTO &inventory_dto);
  static delete_ret_type removeByGoodsRKId(id_type goods_id);

  // other
  static select_ret_type<InventoryDTO> getAll();
  static select_ret_type<InventoryDTO> getByPage(count_type page_size,
                                                 count_type offset);
  static count_type count();
};
