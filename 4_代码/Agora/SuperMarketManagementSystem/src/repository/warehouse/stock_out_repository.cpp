#include <repository/warehouse/stock_out_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type StockOutRepository::create(const StockOutDTO &stock_out_dto) {
    return _insert(stock_out_dto);
};

select_ret_type<StockOutDTO> StockOutRepository::get(const std::string& stock_out_name) {
  return _select(db::stock_out{}.stock_out_name == stock_out_name);
};

update_ret_type StockOutRepository::update(const StockOutDTO &dto) {
    return _update(dto, db::stock_out{}.stock_out_id == dto.stock_out_id);
};

delete_ret_type StockOutRepository::remove(const std::string& stock_out_id) {
  return _remove(db::stock_out{}.stock_out_id == stock_out_id);
}

// Custom Queries
select_ret_type<StockOutDTO> StockOutRepository::getAll() {
  return _select(db::stock_out{}.id >= 0);
}

select_ret_type<StockOutDTO> StockOutRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::stock_out{}.id >= 0, page_size, offset);
}

count_type StockOutRepository::count() { return _count(); }

// 其他方法实现...
