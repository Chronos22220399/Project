#include <repository/member/points_policy_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type PointsPolicyRepository::create(const PointsPolicyDTO &points_policy_dto) {
    return _insert(points_policy_dto);
};

select_ret_type<PointsPolicyDTO> PointsPolicyRepository::get(const std::string& points_policy_name) {
  return _select(db::points_policy{}.points_policy_name == points_policy_name);
};

update_ret_type PointsPolicyRepository::update(const PointsPolicyDTO &dto) {
    return _update(dto, db::points_policy{}.points_policy_id == dto.points_policy_id);
};

delete_ret_type PointsPolicyRepository::remove(const std::string& points_policy_id) {
  return _remove(db::points_policy{}.points_policy_id == points_policy_id);
}

// Custom Queries
select_ret_type<PointsPolicyDTO> PointsPolicyRepository::getAll() {
  return _select(db::points_policy{}.id >= 0);
}

select_ret_type<PointsPolicyDTO> PointsPolicyRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::points_policy{}.id >= 0, page_size, offset);
}

count_type PointsPolicyRepository::count() { return _count(); }

// 其他方法实现...
