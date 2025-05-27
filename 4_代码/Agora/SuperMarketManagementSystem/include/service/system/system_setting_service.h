#pragma once
#include <crow.h>
#include <string>
#include<model/dto/system/system_setting_dto.hpp>

class SystemSettingService {
public:
    static ServiceResult create(SystemSettingDTO &dto);
// static ServiceResult updateByKey(const std::string &ex_id, {} &dto);
// static ServiceResult remove(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
