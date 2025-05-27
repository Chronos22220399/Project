#include <repository/employee/schedule_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type ScheduleRepository::create(const ScheduleDTO &schedule_dto) {
    return _insert(schedule_dto);
};

select_ret_type<ScheduleDTO> ScheduleRepository::get(const std::string& schedule_name) {
  return _select(db::schedule{}.schedule_name == schedule_name);
};

update_ret_type ScheduleRepository::update(const ScheduleDTO &dto) {
    return _update(dto, db::schedule{}.schedule_id == dto.schedule_id);
};

delete_ret_type ScheduleRepository::remove(const std::string& schedule_id) {
  return _remove(db::schedule{}.schedule_id == schedule_id);
}

// Custom Queries
select_ret_type<ScheduleDTO> ScheduleRepository::getAll() {
  return _select(db::schedule{}.id >= 0);
}

select_ret_type<ScheduleDTO> ScheduleRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::schedule{}.id >= 0, page_size, offset);
}

count_type ScheduleRepository::count() { return _count(); }

// 其他方法实现...
