#include <repository/supplier/supplier_contract_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SupplierContractRepository::create(
  const SupplierContractDTO& supplier_contract_dto)
{
  return _insert(supplier_contract_dto);
};

select_ret_type<SupplierContractDTO>
SupplierContractRepository::getBySupplierRKId(const in_id_type supplier_rk_id)
{
  return _select(db::supplier_contract{}.supplier_rk_id == supplier_rk_id);
};

update_ret_type
SupplierContractRepository::updateById(const in_id_type id,
                                       const SupplierContractDTO& dto)
{
  return _update(dto, db::supplier_contract{}.id == id);
};

delete_ret_type SupplierContractRepository::removeById(const in_id_type id)
{
  return _remove(db::supplier_contract{}.id == id);
}

// Custom Queries
select_ret_type<SupplierContractDTO> SupplierContractRepository::getAll()
{
  return _select(db::supplier_contract{}.id >= 0);
}

select_ret_type<SupplierContractDTO>
SupplierContractRepository::getByPage(int page_size, int offset)
{
  return _select_from(db::supplier_contract{}.id >= 0, page_size, offset);
}

count_type SupplierContractRepository::count()
{
  return _count();
}

// 其他方法实现...
