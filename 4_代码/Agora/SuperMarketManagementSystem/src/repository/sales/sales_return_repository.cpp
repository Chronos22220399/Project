#include <repository/sales/sales_return_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SalesReturnRepository::create(const SalesReturnDTO &sales_return_dto) {
    return _insert(sales_return_dto);
};

select_ret_type<SalesReturnDTO> SalesReturnRepository::get(const std::string& sales_return_name) {
  return _select(db::sales_return{}.sales_return_name == sales_return_name);
};

update_ret_type SalesReturnRepository::update(const SalesReturnDTO &dto) {
    return _update(dto, db::sales_return{}.sales_return_id == dto.sales_return_id);
};

delete_ret_type SalesReturnRepository::remove(const std::string& sales_return_id) {
  return _remove(db::sales_return{}.sales_return_id == sales_return_id);
}

// Custom Queries
select_ret_type<SalesReturnDTO> SalesReturnRepository::getAll() {
  return _select(db::sales_return{}.id >= 0);
}

select_ret_type<SalesReturnDTO> SalesReturnRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::sales_return{}.id >= 0, page_size, offset);
}

count_type SalesReturnRepository::count() { return _count(); }

// 其他方法实现...
