#include <model/dto/goods/goods_dto.hpp>
#include <repository/goods_repository.h>
using namespace std;

insert_ret_type GoodsRepository::insert(const GoodsDTO &goods_dto) {
  return _insert(goods_dto);
}

select_ret_type<GoodsDTO> GoodsRepository::getAllGoods() {
  return _select(db::goods{}.id >= 0);
}

select_ret_type<GoodsDTO> GoodsRepository::getGoodsByPage(count_type page_size,
                                                          count_type offset) {
  return _select_from(db::goods{}.id >= 0, page_size, offset);
}

count_type GoodsRepository::count() { return _count(); }
