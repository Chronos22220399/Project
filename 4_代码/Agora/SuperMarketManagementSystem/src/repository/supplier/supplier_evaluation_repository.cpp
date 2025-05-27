#include <repository/supplier/supplier_evaluation_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SupplierEvaluationRepository::create(const SupplierEvaluationDTO &supplier_evaluation_dto) {
    return _insert(supplier_evaluation_dto);
};

select_ret_type<SupplierEvaluationDTO> SupplierEvaluationRepository::get(const std::string& supplier_evaluation_name) {
  return _select(db::supplier_evaluation{}.supplier_evaluation_name == supplier_evaluation_name);
};

update_ret_type SupplierEvaluationRepository::update(const SupplierEvaluationDTO &dto) {
    return _update(dto, db::supplier_evaluation{}.supplier_evaluation_id == dto.supplier_evaluation_id);
};

delete_ret_type SupplierEvaluationRepository::remove(const std::string& supplier_evaluation_id) {
  return _remove(db::supplier_evaluation{}.supplier_evaluation_id == supplier_evaluation_id);
}

// Custom Queries
select_ret_type<SupplierEvaluationDTO> SupplierEvaluationRepository::getAll() {
  return _select(db::supplier_evaluation{}.id >= 0);
}

select_ret_type<SupplierEvaluationDTO> SupplierEvaluationRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::supplier_evaluation{}.id >= 0, page_size, offset);
}

count_type SupplierEvaluationRepository::count() { return _count(); }

// 其他方法实现...
