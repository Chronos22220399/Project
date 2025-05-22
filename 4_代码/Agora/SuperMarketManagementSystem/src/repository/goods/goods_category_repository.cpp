#include <repository/goods/goods_category_repository.h>

// 通用 CRUD（internal）
insert_ret_type
GoodsCategoryRepository::create(const GoodsCategoryDTO& goods_category_dto)
{
  return _insert(goods_category_dto);
}

select_ret_type<GoodsCategoryDTO>
GoodsCategoryRepository::getById(in_id_type id)
{
  return _select(db::goods_category{}.id == id);
}

update_ret_type
GoodsCategoryRepository::updateById(in_id_type id,
                                    const GoodsCategoryDTO& goods_category_dto)
{
  return _update(goods_category_dto, db::goods_category{}.id == id);
}

delete_ret_type GoodsCategoryRepository::removeById(in_id_type id)
{
  return _remove(db::goods_category{}.id == id);
}

bool GoodsCategoryRepository::existsById(in_id_type id)
{
  return _exists(db::goods_category{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<GoodsCategoryDTO> GoodsCategoryRepository::getByGoodsCategoryId(
  const std::string& goods_category_id)
{
  return _select(db::goods_category{}.goods_category_id == goods_category_id);
}

select_ret_type<GoodsCategoryDTO>
GoodsCategoryRepository::getByName(const std::string& goods_category_name)
{
  return _select(db::goods_category{}.goods_category_name
                 == goods_category_name);
}

delete_ret_type GoodsCategoryRepository::removeByGoodsCategoryId(
  const std::string& goods_category_id)
{
  return _remove(db::goods_category{}.goods_category_id == goods_category_id);
}

bool GoodsCategoryRepository::existsByGoodsCategoryId(
  const std::string& goods_category_id)
{
  return _exists(db::goods_category{}.goods_category_id == goods_category_id);
}

// other
select_ret_type<GoodsCategoryDTO> GoodsCategoryRepository::getAll()
{
  return _select(db::goods_category{}.id >= 0);
}

select_ret_type<GoodsCategoryDTO>
GoodsCategoryRepository::getByPage(count_type page_size, count_type offset)
{
  return _select_from(db::goods_category{}.id >= 0, page_size, offset);
}

count_type GoodsCategoryRepository::count()
{
  return _count();
}

// 获取 internal id 用于缓存正向映射
in_id_type
GoodsCategoryRepository::getInternalId(const std::string& goods_category_id)
{
  auto result = utils::DataBaseHelper::execute<in_id_type>(
    [ &goods_category_id ](const utils::pooled_conn_ptr_type& conn_) {
      static db::goods_category goods_category{};
      auto rows = (*conn_)(
        select(goods_category.id)
          .from(goods_category)
          .where(goods_category.goods_category_id == goods_category_id));
      return rows.empty() ? 0 : rows.front().id;
    });
  return result;
}

// 获取 external id 用于缓存逆向映射
std::string GoodsCategoryRepository::getExternalId(in_id_type id)
{
  auto result = utils::DataBaseHelper::execute<std::string>(
    [ id ](const utils::pooled_conn_ptr_type& conn_) {
      static db::goods_category goods_category{};
      auto rows = (*conn_)(select(goods_category.goods_category_id)
                             .from(goods_category)
                             .where(goods_category.id == id));
      return rows.empty() ? std::string() : rows.front().goods_category_id;
    });
  return result;
}
