#include <repository/goods/goods_price_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type GoodsPriceRepository::create(const GoodsPriceDTO &goods_price_dto) {
    return _insert(goods_price_dto);
};

select_ret_type<GoodsPriceDTO> GoodsPriceRepository::get(id_type id) {
  return _select(db::goods_price{}.id == id);
};

update_ret_type GoodsPriceRepository::update(const GoodsPriceDTO &dto) {
    return _update(dto, db::goods_price{}.id == dto.id);
};

delete_ret_type GoodsPriceRepository::remove(id_type id) {
  return _remove(db::goods_price{}.id == id);
}

// Custom Queries
select_ret_type<GoodsPriceDTO> GoodsPriceRepository::getAll() {
  return _select(db::goods_price{}.id >= 0);
}

select_ret_type<GoodsPriceDTO> GoodsPriceRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::goods_price{}.id >= 0, page_size, offset);
}

count_type GoodsPriceRepository::count() { return _count(); }

// 其他方法实现...
