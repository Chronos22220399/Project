#pragma once
#include <common/generic_model.hpp>
#include <model/dto/warehouse/inventory_alert_dto.hpp>

class InventoryAlertRepository
    : public model::GenericModel<InventoryAlertDTO, db::inventory_alert> {
public:
  // CRUD Operations
  static insert_ret_type create(const InventoryAlertDTO &InventoryAlertDTO);
  static select_ret_type<InventoryAlertDTO>
  get(const std::string &inventory_alert_name);
  static update_ret_type
  updateByGoodsRKId(in_id_type goods_rk_id,
                    const InventoryAlertDTO &inventory_alert_dto);
  static delete_ret_type removeByGoodsRKId(in_id_type goods_rk_id);

  // Custom Queries
  static select_ret_type<InventoryAlertDTO> getAll();
  static select_ret_type<InventoryAlertDTO> getByPage(int page_size,
                                                      int offset);
  static count_type count();

  // Foreign Key Relations
  static select_ret_type<InventoryAlertDTO>
  getByGoodsRKId(in_id_type goods_rk_id);
};
