#pragma once
#include <crow.h>
#include <model/dto/system/role_dto.hpp>
#include <string>

class RoleService {
  public:
  static ServiceResult create(RoleDTO& dto);
  static ServiceResult updateByRoleId(const std::string& ex_id, RoleDTO& dto);
  static ServiceResult removeByRoleId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
