#include <repository/warehouse/inventory_alert_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type
InventoryAlertRepository::create(const InventoryAlertDTO &inventory_alert_dto) {
  return _insert(inventory_alert_dto);
};

select_ret_type<InventoryAlertDTO>
InventoryAlertRepository::getByGoodsRKId(in_id_type goods_rk_id) {
  return _select(db::inventory_alert{}.goods_rk_id == goods_rk_id);
};

update_ret_type
InventoryAlertRepository::updateByGoodsRKId(in_id_type goods_rk_id,
                                            const InventoryAlertDTO &dto) {
  return _update(dto, db::inventory_alert{}.goods_rk_id == goods_rk_id);
};

delete_ret_type
InventoryAlertRepository::removeByGoodsRKId(in_id_type goods_rk_id) {
  return _remove(db::inventory_alert{}.goods_rk_id == goods_rk_id);
}

// Custom Queries
select_ret_type<InventoryAlertDTO> InventoryAlertRepository::getAll() {
  return _select(db::inventory_alert{}.id >= 0);
}

select_ret_type<InventoryAlertDTO>
InventoryAlertRepository::getByPage(int page_size, int offset) {
  return _select_from(db::inventory_alert{}.id >= 0, page_size, offset);
}

count_type InventoryAlertRepository::count() { return _count(); }

// 其他方法实现...
