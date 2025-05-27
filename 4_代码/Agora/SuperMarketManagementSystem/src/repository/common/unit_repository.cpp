#include <repository/common/unit_repository.h>

// 通用 CRUD（internal）
insert_ret_type UnitRepository::create(const UnitDTO& unit_dto)
{
  return _insert(unit_dto);
}

select_ret_type<UnitDTO> UnitRepository::getById(in_id_type id)
{
  return _select(db::unit{}.id == id);
}

update_ret_type UnitRepository::updateById(in_id_type id,
                                           const UnitDTO& unit_dto)
{
  return _update(unit_dto, db::unit{}.id == id);
}

delete_ret_type UnitRepository::removeById(in_id_type id)
{
  return _remove(db::unit{}.id == id);
}

bool UnitRepository::existsById(in_id_type id)
{
  return _exists(db::unit{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<UnitDTO> UnitRepository::getByUnitId(const std::string& unit_id)
{
  return _select(db::unit{}.unit_id == unit_id);
}

select_ret_type<UnitDTO> UnitRepository::getByName(const std::string& unit_name)
{
  return _select(db::unit{}.unit_name == unit_name);
}

update_ret_type UnitRepository::updateByUnitId(const std::string& unit_id,
                                               const UnitDTO& unit_dto)
{
  return _update(unit_dto, db::unit{}.unit_id == unit_id);
}

delete_ret_type UnitRepository::removeByUnitId(const std::string& unit_id)
{
  return _remove(db::unit{}.unit_id == unit_id);
}

bool UnitRepository::existsByUnitId(const std::string& unit_id)
{
  return _exists(db::unit{}.unit_id == unit_id);
}

// other
select_ret_type<UnitDTO> UnitRepository::getAll()
{
  return _select(db::unit{}.id >= 0);
}

select_ret_type<UnitDTO> UnitRepository::getByPage(count_type page_size,
                                                   count_type offset)
{
  return _select_from(db::unit{}.id >= 0, page_size, offset);
}

count_type UnitRepository::count()
{
  return _count();
}

in_id_type UnitRepository::getInternalId(const ex_id_type& unit_id)
{
  return utils::DataBaseHelper::execute<in_id_type>(
    [ &unit_id ](const utils::pooled_conn_ptr_type& conn_) {
      static auto unit = db::unit{};
      auto result =
        (*conn_)(select(unit.id).from(unit).where(unit.unit_id == unit_id));
      return result.empty() ? 0 : result.front().id;
    });
}

ex_id_type UnitRepository::getExternalId(in_id_type id)
{
  return utils::DataBaseHelper::execute<ex_id_type>(
    [ &id ](const utils::pooled_conn_ptr_type& conn_) {
      static auto unit = db::unit{};
      auto result =
        (*conn_)(select(unit.unit_id).from(unit).where(unit.id == id));
      return result.empty() ? std::string() : result.front().unit_id;
    });
}
