#include <repository/warehouse/inventory_check_order_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type InventoryCheckOrderRepository::create(const InventoryCheckOrderDTO &inventory_check_order_dto) {
    return _insert(inventory_check_order_dto);
};

select_ret_type<InventoryCheckOrderDTO> InventoryCheckOrderRepository::getById(const in_id_type id) {
  return _select(db::inventory_check_order{}.id == id);
};

update_ret_type InventoryCheckOrderRepository::updateById(const in_id_type id, const InventoryCheckOrderDTO &dto) {
    return _update(dto, db::inventory_check_order{}.id == id);
};

delete_ret_type InventoryCheckOrderRepository::removeById(const in_id_type id) {
  return _remove(db::inventory_check_order{}.id == id);
}

// Custom Queries
select_ret_type<InventoryCheckOrderDTO> InventoryCheckOrderRepository::getAll() {
  return _select(db::inventory_check_order{}.id >= 0);
}

select_ret_type<InventoryCheckOrderDTO> InventoryCheckOrderRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::inventory_check_order{}.id >= 0, page_size, offset);
}

count_type InventoryCheckOrderRepository::count() { return _count(); }

// 其他方法实现...
