#pragma once
#include <crow.h>
#include <string>
#include <model/dto/supplier/purchase_order_dto.hpp>

class PurchaseOrderService {
public:
    static ServiceResult create(PurchaseOrderDTO &dto);
static ServiceResult updateByPurchaseOrderId(const std::string &ex_id, PurchaseOrderDTO &dto);
static ServiceResult removeByPurchaseOrderId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
