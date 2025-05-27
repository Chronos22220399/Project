#include <repository/employee/position_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type PositionRepository::create(const PositionDTO &position_dto) {
    return _insert(position_dto);
};

select_ret_type<PositionDTO> PositionRepository::get(const std::string& position_name) {
  return _select(db::position{}.position_name == position_name);
};

update_ret_type PositionRepository::update(const PositionDTO &dto) {
    return _update(dto, db::position{}.position_id == dto.position_id);
};

delete_ret_type PositionRepository::remove(const std::string& position_id) {
  return _remove(db::position{}.position_id == position_id);
}

// Custom Queries
select_ret_type<PositionDTO> PositionRepository::getAll() {
  return _select(db::position{}.id >= 0);
}

select_ret_type<PositionDTO> PositionRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::position{}.id >= 0, page_size, offset);
}

count_type PositionRepository::count() { return _count(); }

// 其他方法实现...
