#pragma once
#include <crow.h>
#include <string>
#include<model/dto/employee/schedule_dto.hpp>

class ScheduleService {
public:
    static ServiceResult create(ScheduleDTO &dto);
static ServiceResult updateByScheduleId(const std::string &ex_id, ScheduleDTO &dto);
static ServiceResult removeByScheduleId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
