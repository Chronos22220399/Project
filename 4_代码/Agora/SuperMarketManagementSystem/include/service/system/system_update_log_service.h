#pragma once
#include <crow.h>
#include <string>
#include<model/dto/system/system_update_log_dto.hpp>

class SystemUpdateLogService {
public:
    static ServiceResult create(SystemUpdateLogDTO &dto);
static ServiceResult updateBySystemUpdateId(const std::string &ex_id, SystemUpdateLogDTO &dto);
static ServiceResult removeBySysremUpdateId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
