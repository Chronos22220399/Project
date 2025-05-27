#include <repository/system/user_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type UserRepository::create(const UserDTO& user_dto)
{
  return _insert(user_dto);
};

select_ret_type<UserDTO>
UserRepository::getUserByUsername(const std::string& username)
{
  return _select(db::user{}.username == username);
};

update_ret_type UserRepository::updateById(const in_id_type id,
                                           const UserDTO& dto)
{
  return _update(dto, db::user{}.id == dto.id);
};

delete_ret_type UserRepository::remove(const std::string& user_id)
{
  return _remove(db::user{}.user_id == user_id);
}

// Custom Queries
select_ret_type<UserDTO> UserRepository::getAll()
{
  return _select(db::user{}.id >= 0);
}

select_ret_type<UserDTO> UserRepository::getByPage(int page_size, int offset)
{
  return _select_from(db::user{}.id >= 0, page_size, offset);
}

count_type UserRepository::count()
{
  return _count();
}

bool UserRepository::findUserName(const std::string& username)
{
  auto res = getUserByUsername(username);
  return !res.empty();
}

bool UserRepository::findPhone(const std::string& phone_number)
{
  auto res = _select(db::user{}.phone_number == phone_number);
  return !res.empty();
}
// 其他方法实现...
