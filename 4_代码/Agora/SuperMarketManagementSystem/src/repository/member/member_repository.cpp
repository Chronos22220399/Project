#include <repository/member/member_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type MemberRepository::create(const MemberDTO& member_dto)
{
  return _insert(member_dto);
};

update_ret_type MemberRepository::update(const MemberDTO& dto)
{
  return _update(dto, db::member{}.member_id == dto.member_id);
};

delete_ret_type MemberRepository::remove(const std::string& member_id)
{
  return _remove(db::member{}.member_id == member_id);
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

// 其他方法实现...
