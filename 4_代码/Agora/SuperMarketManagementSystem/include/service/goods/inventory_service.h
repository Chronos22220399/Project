#pragma once
#include <crow.h>
#include <string>

// 库存表具备增、查、改的功能，库存的删除一定是由商品或仓库的删除造成的，因此这里不会写上删除服务
class InventoryService {
public:
  // create
  static crow::response create(const std::string &body);
  // get
  static crow::response getByGoodsId(const std::string &body);
  static crow::response getByWarehouseId(const std::string &body);
  static crow::response getByPage(const std::string &body);
  static crow::response getAll();
  // update
  static crow::response updateByGoodsId(const std::string &body);
};
