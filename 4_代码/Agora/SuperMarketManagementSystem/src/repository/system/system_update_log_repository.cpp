#include <repository/system/system_update_log_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SystemUpdateLogRepository::create(const SystemUpdateLogDTO &system_update_log_dto) {
    return _insert(system_update_log_dto);
};

select_ret_type<SystemUpdateLogDTO> SystemUpdateLogRepository::get(const std::string& system_update_log_name) {
  return _select(db::system_update_log{}.system_update_log_name == system_update_log_name);
};

update_ret_type SystemUpdateLogRepository::update(const SystemUpdateLogDTO &dto) {
    return _update(dto, db::system_update_log{}.system_update_log_id == dto.system_update_log_id);
};

delete_ret_type SystemUpdateLogRepository::remove(const std::string& system_update_log_id) {
  return _remove(db::system_update_log{}.system_update_log_id == system_update_log_id);
}

// Custom Queries
select_ret_type<SystemUpdateLogDTO> SystemUpdateLogRepository::getAll() {
  return _select(db::system_update_log{}.id >= 0);
}

select_ret_type<SystemUpdateLogDTO> SystemUpdateLogRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::system_update_log{}.id >= 0, page_size, offset);
}

count_type SystemUpdateLogRepository::count() { return _count(); }

// 其他方法实现...
