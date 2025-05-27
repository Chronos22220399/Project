#include <repository/warehouse/stock_out_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type StockOutRepository::create(const StockOutDTO& stock_out_dto)
{
  return _insert(stock_out_dto);
};


update_ret_type StockOutRepository::updateById(const in_id_type id,
                                               const StockOutDTO& dto)
{
  return _update(dto, db::stock_out{}.id == id);
};

delete_ret_type StockOutRepository::removeById(const in_id_type id)
{
  return _remove(db::stock_out{}.id == id);
}

// Custom Queries
select_ret_type<StockOutDTO> StockOutRepository::getAll()
{
  return _select(db::stock_out{}.id >= 0);
}

select_ret_type<StockOutDTO> StockOutRepository::getByPage(int page_size,
                                                           int offset)
{
  return _select_from(db::stock_out{}.id >= 0, page_size, offset);
}

count_type StockOutRepository::count()
{
  return _count();
}

in_id_type StockOutRepository::getInternalId(const std::string& stock_out_id)
{
  auto result = utils::DataBaseHelper::execute<in_id_type>(
    [ &stock_out_id ](const utils::pooled_conn_ptr_type& conn_) {
      static db::stock_out stock_out{};
      auto rows = (*conn_)(select(stock_out.id)
                             .from(stock_out)
                             .where(stock_out.stock_out_id == stock_out_id));
      return rows.empty() ? 0 : rows.front().id;
    });
  return result;
}

ex_id_type StockOutRepository::getExternalId(in_id_type id)
{
  auto result = utils::DataBaseHelper::execute<ex_id_type>(
    [ &id ](const utils::pooled_conn_ptr_type& conn_) {
      static db::stock_out stock_out{};
      auto rows = (*conn_)(select(stock_out.stock_out_id)
                             .from(stock_out)
                             .where(stock_out.id == id));
      return rows.empty() ? std::string() : rows.front().stock_out_id;
    });
  return result;
}

// 其他方法实现...
// 其他方法实现...
