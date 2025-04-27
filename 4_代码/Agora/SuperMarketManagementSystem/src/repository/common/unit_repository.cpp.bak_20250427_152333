#include <repository/common/unit_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type UnitRepository::create(const UnitDTO &unit_dto) {
    return _insert(unit_dto);
};

select_ret_type<UnitDTO> UnitRepository::get(id_type id) {
  return _select(db::unit{}.id == id);
};

update_ret_type UnitRepository::update(const UnitDTO &dto) {
    return _update(dto, db::unit{}.id == dto.id);
};

delete_ret_type UnitRepository::remove(id_type id) {
  return _remove(db::unit{}.id == id);
}

// Custom Queries
select_ret_type<UnitDTO> UnitRepository::getAll() {
  return _select(db::unit{}.id >= 0);
}

select_ret_type<UnitDTO> UnitRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::unit{}.id >= 0, page_size, offset);
}

count_type UnitRepository::count() { return _count(); }

// 其他方法实现...
