#pragma once
#include <common/common_utils.hpp>
#include <crow.h>
#include <string>
// model
#include <model/dto/goods/inventory_dto.hpp>

// 库存表具备增、查、改的功能，库存的删除一定是由商品或仓库的删除造成的，因此这里不会写上删除服务
class InventoryService {
  public:
  // create
  static ServiceResult create(InventoryDTO& inventory_dto);
  // get
  static ServiceResult getByGoodsId(const std::string& goods_id);
  static ServiceResult getByWarehouseId(const std::string& warehouse_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
  // update
  static ServiceResult updateByGoodsId(const in_id_type goods_rk_id,
                                       InventoryDTO& inventory_dto);
};
