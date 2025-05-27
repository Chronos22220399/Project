#pragma once
#include <crow.h>
#include <string>
#include <model/dto/supplier/supplier_evaluation_dto.hpp>

class SupplierEvaluationService {
public:
    static ServiceResult create(SupplierEvaluationDTO &dto);
static ServiceResult updateBySupplierEvaluationId(const std::string &ex_id,SupplierEvaluationDTO &dto);
static ServiceResult removeBySupplierEvaluationId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
