#include <repository/sales/sales_order_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type
SalesOrderRepository::create(const SalesOrderDTO& sales_order_dto)
{
  return _insert(sales_order_dto);
};

select_ret_type<SalesOrderDTO>
SalesOrderRepository::get(const std::string& sales_order_id)
{
  return _select(db::sales_order{}.order_id == sales_order_id);
};

update_ret_type SalesOrderRepository::updateById(const SalesOrderDTO& dto)
{
  return _update(dto, db::sales_order{}.id == dto.id);
};

delete_ret_type SalesOrderRepository::removeById(const in_id_type id)
{
  return _remove(db::sales_order{}.id == id);
}

// Custom Queries
select_ret_type<SalesOrderDTO> SalesOrderRepository::getAll()
{
  return _select(db::sales_order{}.id >= 0);
}

select_ret_type<SalesOrderDTO> SalesOrderRepository::getByPage(int page_size,
                                                               int offset)
{
  return _select_from(db::sales_order{}.id >= 0, page_size, offset);
}

count_type SalesOrderRepository::count()
{
  return _count();
}

// 其他方法实现...
