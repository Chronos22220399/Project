#pragma once
#include <crow.h>S
#include <string>
#include <model/dto/system/permission_dto.hpp>

class PermissionService {
public:
    static ServiceResult create(PermissionDTO &dto);
static ServiceResult updateByPermissionId(const std::string &ex_id, PermissionDTO &dto);
static ServiceResult removeByPermissionId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
