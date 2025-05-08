#include <repository/goods/inventory_repository.h>

// 通用 CRUD（internal）
insert_ret_type InventoryRepository::create(const InventoryDTO &inventory_dto) {
  return _insert(inventory_dto);
}

select_ret_type<InventoryDTO> InventoryRepository::getById(in_id_type id) {
  return _select(db::inventory{}.id == id);
}

update_ret_type
InventoryRepository::updateById(in_id_type id,
                                const InventoryDTO &inventory_dto) {
  return _update(inventory_dto, db::inventory{}.id == id);
}

delete_ret_type InventoryRepository::removeById(in_id_type id) {
  return _remove(db::inventory{}.id == id);
}

bool InventoryRepository::existsById(in_id_type id) {
  return _exists(db::inventory{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<InventoryDTO>
InventoryRepository::getByGoodsRKId(in_id_type goods_rk_id) {
  return _select(db::inventory{}.goods_rk_id == goods_rk_id);
}

select_ret_type<InventoryDTO>
InventoryRepository::getByWarehouseRKId(in_id_type warehouse_rk_id) {
  return _select(db::inventory{}.warehouse_rk_id == warehouse_rk_id);
}

update_ret_type
InventoryRepository::updateByGoodsRKId(in_id_type goods_rk_id,
                                       const InventoryDTO &inventory_dto) {
  return _update(inventory_dto, db::inventory{}.goods_rk_id == goods_rk_id);
}

delete_ret_type InventoryRepository::removeByGoodsRKId(in_id_type goods_rk_id) {
  return _remove(db::inventory{}.goods_rk_id == goods_rk_id);
}

// other
select_ret_type<InventoryDTO> InventoryRepository::getAll() {
  return _select(db::inventory{}.id >= 0);
}

select_ret_type<InventoryDTO>
InventoryRepository::getByPage(count_type page_size, count_type offset) {
  return _select_from(db::inventory{}.id >= 0, page_size, offset);
}

count_type InventoryRepository::count() { return _count(); }
