#include <repository/warehouse/warehouse_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type WarehouseRepository::create(const WarehouseDTO &warehouse_dto) {
    return _insert(warehouse_dto);
};

select_ret_type<WarehouseDTO> WarehouseRepository::get(id_type id) {
  return _select(db::warehouse{}.id == id);
};

update_ret_type WarehouseRepository::update(const WarehouseDTO &dto) {
    return _update(dto, db::warehouse{}.id == dto.id);
};

delete_ret_type WarehouseRepository::remove(id_type id) {
  return _remove(db::warehouse{}.id == id);
}

// Custom Queries
select_ret_type<WarehouseDTO> WarehouseRepository::getAll() {
  return _select(db::warehouse{}.id >= 0);
}

select_ret_type<WarehouseDTO> WarehouseRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::warehouse{}.id >= 0, page_size, offset);
}

count_type WarehouseRepository::count() { return _count(); }

// 其他方法实现...
