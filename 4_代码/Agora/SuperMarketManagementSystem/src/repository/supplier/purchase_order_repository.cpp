#include <repository/supplier/purchase_order_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type
PurchaseOrderRepository::create(const PurchaseOrderDTO& purchase_order_dto)
{
  return _insert(purchase_order_dto);
};

select_ret_type<PurchaseOrderDTO>
PurchaseOrderRepository::getBySupplierRKId(const in_id_type supplier_rk_id)
{
  return _select(db::purchase_order{}.supplier_rk_id == supplier_rk_id);
};

update_ret_type PurchaseOrderRepository::updateById(const in_id_type id,
                                                    const PurchaseOrderDTO& dto)
{
  return _update(dto, db::purchase_order{}.id == id);
};

delete_ret_type PurchaseOrderRepository::removeById(const in_id_type id)
{
  return _remove(db::purchase_order{}.id == id);
}

// Custom Queries
select_ret_type<PurchaseOrderDTO> PurchaseOrderRepository::getAll()
{
  return _select(db::purchase_order{}.id >= 0);
}

select_ret_type<PurchaseOrderDTO>
PurchaseOrderRepository::getByPage(int page_size, int offset)
{
  return _select_from(db::purchase_order{}.id >= 0, page_size, offset);
}

count_type PurchaseOrderRepository::count()
{
  return _count();
}

// 其他方法实现...
