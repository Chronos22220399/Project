#include <repository/common/unit_repository.h>

// 通用 CRUD（internal）
insert_ret_type UnitRepository::create(const UnitDTO &unit_dto) {
  return _insert(unit_dto);
}

select_ret_type<UnitDTO> UnitRepository::getById(id_type id) {
  return _select(db::unit{}.id == id);
}

update_ret_type UnitRepository::updateById(id_type id,
                                           const UnitDTO &unit_dto) {
  return _update(unit_dto, db::unit{}.id == id);
}

delete_ret_type UnitRepository::removeById(id_type id) {
  return _remove(db::unit{}.id == id);
}

bool UnitRepository::existsById(id_type id) {
  return _exists(db::unit{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<UnitDTO>
UnitRepository::getByUnitId(const std::string &unit_id) {
  return _select(db::unit{}.unit_id == unit_id);
}

select_ret_type<UnitDTO>
UnitRepository::getByName(const std::string &unit_name) {
  return _select(db::unit{}.unit_name == unit_name);
}

update_ret_type UnitRepository::updateByUnitId(const std::string &unit_id,
                                               const UnitDTO &unit_dto) {
  return _update(unit_dto, db::unit{}.unit_id == unit_id);
}

delete_ret_type UnitRepository::removeByUnitId(const std::string &unit_id) {
  return _remove(db::unit{}.unit_id == unit_id);
}

bool UnitRepository::existsByUnitId(const std::string &unit_id) {
  return _exists(db::unit{}.unit_id == unit_id);
}

// other
select_ret_type<UnitDTO> UnitRepository::getAll() {
  return _select(db::unit{}.id >= 0);
}

select_ret_type<UnitDTO> UnitRepository::getByPage(count_type page_size,
                                                   count_type offset) {
  return _select_from(db::unit{}.id >= 0, page_size, offset);
}

count_type UnitRepository::count() { return _count(); }
