#pragma once
#include <common/generic_model.hpp>
#include <model/dto/system/role_dto.hpp>

class RoleRepository : public model::GenericModel<RoleDTO, db::role> {
  public:
  // CRUD Operations
  static insert_ret_type create(const RoleDTO& RoleDTO);
  static select_ret_type<RoleDTO> get(const std::string& role_name);
  static update_ret_type updateById(const in_id_type id,
                                    const RoleDTO& role_dto);
  static delete_ret_type removeById(const in_id_type id);

  // Custom Queries
  static select_ret_type<RoleDTO> getAll();
  static select_ret_type<RoleDTO> getByPage(int page_size, int offset);
  static count_type count();


  // Foreign Key Relations
};
