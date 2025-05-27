#include <repository/system/system_setting_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type SystemSettingRepository::create(const SystemSettingDTO &system_setting_dto) {
    return _insert(system_setting_dto);
};

select_ret_type<SystemSettingDTO> SystemSettingRepository::get(const std::string& system_setting_name) {
  return _select(db::system_setting{}.system_setting_name == system_setting_name);
};

update_ret_type SystemSettingRepository::update(const SystemSettingDTO &dto) {
    return _update(dto, db::system_setting{}.system_setting_id == dto.system_setting_id);
};

delete_ret_type SystemSettingRepository::remove(const std::string& system_setting_id) {
  return _remove(db::system_setting{}.system_setting_id == system_setting_id);
}

// Custom Queries
select_ret_type<SystemSettingDTO> SystemSettingRepository::getAll() {
  return _select(db::system_setting{}.id >= 0);
}

select_ret_type<SystemSettingDTO> SystemSettingRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::system_setting{}.id >= 0, page_size, offset);
}

count_type SystemSettingRepository::count() { return _count(); }

// 其他方法实现...
