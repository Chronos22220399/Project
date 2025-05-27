#pragma once
#include <common/generic_model.hpp>
#include <model/dto/system/user_dto.hpp>

class UserRepository : public model::GenericModel<UserDTO, db::user> {
  public:
  // CRUD Operations
  static insert_ret_type create(const UserDTO& UserDTO);
  static select_ret_type<UserDTO>
  getUserByUsername(const std::string& user_name);
  static update_ret_type updateById(const in_id_type id,
                                    const UserDTO& user_dto);
  static delete_ret_type remove(const std::string& user_id);

  // Custom Queries
  static select_ret_type<UserDTO> getAll();
  static select_ret_type<UserDTO> getByPage(int page_size, int offset);
  static count_type count();

  static bool findUserName(const std::string& username);
  static bool findPhone(const std::string& phone_number);

  // Foreign Key Relations
};
