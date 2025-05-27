#pragma once
#include <crow.h>
#include <string>

class PointsExchangeRecordService {
public:
    static ServiceResult create({} &dto);
static ServiceResult update(const std::string &ex_id, {} &dto);
static ServiceResult remove(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
