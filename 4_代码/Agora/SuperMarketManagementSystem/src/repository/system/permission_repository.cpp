#include <repository/system/permission_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type PermissionRepository::create(const PermissionDTO &permission_dto) {
    return _insert(permission_dto);
};

select_ret_type<PermissionDTO> PermissionRepository::get(const std::string& permission_name) {
  return _select(db::permission{}.permission_name == permission_name);
};

update_ret_type PermissionRepository::update(const PermissionDTO &dto) {
    return _update(dto, db::permission{}.permission_id == dto.permission_id);
};

delete_ret_type PermissionRepository::remove(const std::string& permission_id) {
  return _remove(db::permission{}.permission_id == permission_id);
}

// Custom Queries
select_ret_type<PermissionDTO> PermissionRepository::getAll() {
  return _select(db::permission{}.id >= 0);
}

select_ret_type<PermissionDTO> PermissionRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::permission{}.id >= 0, page_size, offset);
}

count_type PermissionRepository::count() { return _count(); }

// 其他方法实现...
