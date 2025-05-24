#pragma once
#include <crow.h>
#include <string>
#include <common/include.h>
#include <model/dto/warehouse/inventory_check_order_dto.hpp>

class InventoryCheckOrderService {
public:
    static ServiceResult create(InventoryCheckOrderDTO &dto);
static ServiceResult updateByOrderId(const std::string &ex_id, InventoryCheckOrderDTO &dto);
static ServiceResult removeByOrderId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
