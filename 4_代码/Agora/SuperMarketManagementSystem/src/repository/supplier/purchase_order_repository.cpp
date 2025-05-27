#include <repository/supplier/purchase_order_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type PurchaseOrderRepository::create(const PurchaseOrderDTO &purchase_order_dto) {
    return _insert(purchase_order_dto);
};

select_ret_type<PurchaseOrderDTO> PurchaseOrderRepository::get(const std::string& purchase_order_name) {
  return _select(db::purchase_order{}.purchase_order_name == purchase_order_name);
};

update_ret_type PurchaseOrderRepository::update(const PurchaseOrderDTO &dto) {
    return _update(dto, db::purchase_order{}.purchase_order_id == dto.purchase_order_id);
};

delete_ret_type PurchaseOrderRepository::remove(const std::string& purchase_order_id) {
  return _remove(db::purchase_order{}.purchase_order_id == purchase_order_id);
}

// Custom Queries
select_ret_type<PurchaseOrderDTO> PurchaseOrderRepository::getAll() {
  return _select(db::purchase_order{}.id >= 0);
}

select_ret_type<PurchaseOrderDTO> PurchaseOrderRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::purchase_order{}.id >= 0, page_size, offset);
}

count_type PurchaseOrderRepository::count() { return _count(); }

// 其他方法实现...
