#include <repository/supplier/supplier_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SupplierRepository::create(const SupplierDTO &supplier_dto) {
    return _insert(supplier_dto);
};

select_ret_type<SupplierDTO> SupplierRepository::get(const std::string& supplier_name) {
  return _select(db::supplier{}.supplier_name == supplier_name);
};

update_ret_type SupplierRepository::update(const SupplierDTO &dto) {
    return _update(dto, db::supplier{}.supplier_id == dto.supplier_id);
};

delete_ret_type SupplierRepository::remove(const std::string& supplier_id) {
  return _remove(db::supplier{}.supplier_id == supplier_id);
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
