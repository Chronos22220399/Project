#pragma once
#include <crow.h>
#include <string>
#include <model/dto/employee/position_dto.hpp>

class PositionService {
public:
    static ServiceResult create(PositionDTO &dto);
static ServiceResult updateByPositionId(const std::string &ex_id, PositionDTO &dto);
static ServiceResult removeByPositionId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
