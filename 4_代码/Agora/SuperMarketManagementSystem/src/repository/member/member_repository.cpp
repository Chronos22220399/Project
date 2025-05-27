#include <repository/member/member_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type MemberRepository::create(const MemberDTO& member_dto)
{
  return _insert(member_dto);
};

update_ret_type MemberRepository::updateById(const in_id_type id,
                                             const MemberDTO& dto)
{
  return _update(dto, db::member{}.id == id);
};

delete_ret_type MemberRepository::removeById(const in_id_type id)
{
  return _remove(db::member{}.id == id);
}

// Custom Queries
select_ret_type<MemberDTO> MemberRepository::getAll()
{
  return _select(db::member{}.id >= 0);
}

select_ret_type<MemberDTO> MemberRepository::getByPage(int page_size,
                                                       int offset)
{
  return _select_from(db::member{}.id >= 0, page_size, offset);
}

count_type MemberRepository::count()
{
  return _count();
}

std::optional<in_id_type>
MemberRepository::findMemberByUserRKId(const in_id_type& user_rk_id)
{
  auto res = _select(db::member{}.user_rk_id == user_rk_id);
  if (res.empty() || res.size() > 1)
    return std::nullopt;
  return res.front().id;
}
// 其他方法实现...
