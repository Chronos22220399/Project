#include <repository/goods/inventory_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type InventoryRepository::create(const InventoryDTO &inventory_dto) {
  return _insert(inventory_dto);
};

select_ret_type<InventoryDTO> InventoryRepository::get(id_type id) {
  return _select(db::inventory{}.id == id);
};

update_ret_type InventoryRepository::update(const InventoryDTO &dto) {
  return _update(dto, db::inventory{}.id == dto.id);
};

delete_ret_type InventoryRepository::remove(id_type id) {
  return _remove(db::inventory{}.id == id);
}

// Custom Queries
select_ret_type<InventoryDTO> InventoryRepository::getAll() {
  return _select(db::inventory{}.id >= 0);
}

select_ret_type<InventoryDTO> InventoryRepository::getByPage(int page_size,
                                                             int offset) {
  return _select_from(db::inventory{}.id >= 0, page_size, offset);
}

count_type InventoryRepository::count() { return _count(); }

// 其他方法实现...
