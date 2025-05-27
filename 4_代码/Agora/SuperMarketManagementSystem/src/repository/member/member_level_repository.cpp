#include <repository/member/member_level_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type
MemberLevelRepository::create(const MemberLevelDTO& member_level_dto)
{
  return _insert(member_level_dto);
};

select_ret_type<MemberLevelDTO>
MemberLevelRepository::get(const std::string& member_level_name)
{
  return _select(db::member_level{}.level_name == member_level_name);
};

update_ret_type MemberLevelRepository::updateById(const in_id_type id,
                                                  const MemberLevelDTO& dto)
{
  return _update(dto, db::member_level{}.id == id);
};

delete_ret_type MemberLevelRepository::removeById(const in_id_type id)
{
  return _remove(db::member_level{}.id == id);
}

// Custom Queries
select_ret_type<MemberLevelDTO> MemberLevelRepository::getAll()
{
  return _select(db::member_level{}.id >= 0);
}

select_ret_type<MemberLevelDTO> MemberLevelRepository::getByPage(int page_size,
                                                                 int offset)
{
  return _select_from(db::member_level{}.id >= 0, page_size, offset);
}

count_type MemberLevelRepository::count()
{
  return _count();
}

// 其他方法实现...
