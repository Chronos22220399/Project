#pragma once
#include <crow.h>
#include <string>
#include <model/dto/sales/sales_return_dto.hpp>
class SalesReturnService {
public:
    static ServiceResult create(SalesReturnDTO &dto);
static ServiceResult updateBySalesReturnId(const std::string& ex_id,SalesReturnDTO & dto);
static ServiceResult removeBySalesReturnId(const std::string& ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
