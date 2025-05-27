#include <repository/supplier/supplier_evaluation_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SupplierEvaluationRepository::create(
  const SupplierEvaluationDTO& supplier_evaluation_dto)
{
  return _insert(supplier_evaluation_dto);
};

select_ret_type<SupplierEvaluationDTO>
SupplierEvaluationRepository::getBySupplierRKId(const in_id_type supplier_rk_id)
{
  return _select(db::supplier_evaluation{}.supplier_rk_id == supplier_rk_id);
};

update_ret_type
SupplierEvaluationRepository::updateById(const in_id_type id,
                                         const SupplierEvaluationDTO& dto)
{
  return _update(dto, db::supplier_evaluation{}.id == id);
};

delete_ret_type SupplierEvaluationRepository::removeById(const in_id_type id)
{
  return _remove(db::supplier_evaluation{}.id == id);
}

// Custom Queries
select_ret_type<SupplierEvaluationDTO> SupplierEvaluationRepository::getAll()
{
  return _select(db::supplier_evaluation{}.id >= 0);
}

select_ret_type<SupplierEvaluationDTO>
SupplierEvaluationRepository::getByPage(int page_size, int offset)
{
  return _select_from(db::supplier_evaluation{}.id >= 0, page_size, offset);
}

count_type SupplierEvaluationRepository::count()
{
  return _count();
}

// 其他方法实现...
