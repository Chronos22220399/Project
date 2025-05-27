#include <repository/system/role_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type RoleRepository::create(const RoleDTO &role_dto) {
    return _insert(role_dto);
};

select_ret_type<RoleDTO> RoleRepository::get(const std::string& role_name) {
  return _select(db::role{}.role_name == role_name);
};

update_ret_type RoleRepository::update(const RoleDTO &dto) {
    return _update(dto, db::role{}.role_id == dto.role_id);
};

delete_ret_type RoleRepository::remove(const std::string& role_id) {
  return _remove(db::role{}.role_id == role_id);
}

// Custom Queries
select_ret_type<RoleDTO> RoleRepository::getAll() {
  return _select(db::role{}.id >= 0);
}

select_ret_type<RoleDTO> RoleRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::role{}.id >= 0, page_size, offset);
}

count_type RoleRepository::count() { return _count(); }

// 其他方法实现...
