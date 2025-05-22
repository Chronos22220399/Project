#include <repository/warehouse/inventory_check_order_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type InventoryCheckOrderRepository::create(const InventoryCheckOrderDTO &inventory_check_order_dto) {
    return _insert(inventory_check_order_dto);
};

select_ret_type<InventoryCheckOrderDTO> InventoryCheckOrderRepository::get(const std::string& inventory_check_order_name) {
  return _select(db::inventory_check_order{}.inventory_check_order_name == inventory_check_order_name);
};

update_ret_type InventoryCheckOrderRepository::update(const InventoryCheckOrderDTO &dto) {
    return _update(dto, db::inventory_check_order{}.inventory_check_order_id == dto.inventory_check_order_id);
};

delete_ret_type InventoryCheckOrderRepository::remove(const std::string& inventory_check_order_id) {
  return _remove(db::inventory_check_order{}.inventory_check_order_id == inventory_check_order_id);
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
