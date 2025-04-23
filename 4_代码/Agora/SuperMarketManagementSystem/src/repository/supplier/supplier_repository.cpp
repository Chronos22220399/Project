#include <repository/supplier/supplier_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SupplierRepository::create(const SupplierDTO &dto) {
    return _insert(dto);
};

select_ret_type<SupplierDTO> SupplierRepository::get(id_type id) {
  return _select(db::supplier{}.id == id);
};

update_ret_type SupplierRepository::update(const SupplierDTO &dto) {
    return _update(dto, db::supplier{}.id == dto.id);
};

delete_ret_type SupplierRepository::remove(id_type id) {
  return _remove(db::supplier{}.id == id);
}

// Custom Queries
select_ret_type<SupplierDTO> SupplierRepository::getAll() {
  return _select(db::supplier{}.id >= 0);
}

select_ret_type<SupplierDTO> SupplierRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::supplier{}.id >= 0, page_size, offset);
}

count_type SupplierRepository::count() { return _count(); }

// 其他方法实现...
