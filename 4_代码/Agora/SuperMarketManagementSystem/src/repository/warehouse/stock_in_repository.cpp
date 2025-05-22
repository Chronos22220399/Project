#include <repository/warehouse/stock_in_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type StockInRepository::create(const StockInDTO& stock_in_dto)
{
  return _insert(stock_in_dto);
};

select_ret_type<StockInDTO> StockInRepository::get(const in_id_type id)
{
  return _select(db::stock_in{}.id == id);
};

update_ret_type StockInRepository::update(const StockInDTO& dto)
{
  return _update(dto, db::stock_in{}.stock_in_id == dto.stock_in_id);
};

delete_ret_type StockInRepository::remove(const std::string& stock_in_id)
{
  return _remove(db::stock_in{}.stock_in_id == stock_in_id);
}

// Custom Queries
select_ret_type<StockInDTO> StockInRepository::getAll()
{
  return _select(db::stock_in{}.id >= 0);
}

select_ret_type<StockInDTO> StockInRepository::getByPage(int page_size,
                                                         int offset)
{
  return _select_from(db::stock_in{}.id >= 0, page_size, offset);
}

count_type StockInRepository::count()
{
  return _count();
}

// 其他方法实现...
