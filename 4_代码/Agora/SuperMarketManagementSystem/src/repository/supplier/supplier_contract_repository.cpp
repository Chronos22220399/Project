#include <repository/supplier/supplier_contract_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SupplierContractRepository::create(const SupplierContractDTO &supplier_contract_dto) {
    return _insert(supplier_contract_dto);
};

select_ret_type<SupplierContractDTO> SupplierContractRepository::get(const std::string& supplier_contract_name) {
  return _select(db::supplier_contract{}.supplier_contract_name == supplier_contract_name);
};

update_ret_type SupplierContractRepository::update(const SupplierContractDTO &dto) {
    return _update(dto, db::supplier_contract{}.supplier_contract_id == dto.supplier_contract_id);
};

delete_ret_type SupplierContractRepository::remove(const std::string& supplier_contract_id) {
  return _remove(db::supplier_contract{}.supplier_contract_id == supplier_contract_id);
}

// Custom Queries
select_ret_type<SupplierContractDTO> SupplierContractRepository::getAll() {
  return _select(db::supplier_contract{}.id >= 0);
}

select_ret_type<SupplierContractDTO> SupplierContractRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::supplier_contract{}.id >= 0, page_size, offset);
}

count_type SupplierContractRepository::count() { return _count(); }

// 其他方法实现...
