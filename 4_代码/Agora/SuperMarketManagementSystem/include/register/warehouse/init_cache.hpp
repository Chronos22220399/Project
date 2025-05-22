//
// Created by 无铭 on 25-5-22.
//

#pragma once
#include <common/global_id_cache.hpp>
#include <repository/warehouse/warehouse_repository.h>
#include <repository/warehouse/stock_in_repository.h>

namespace warehouse {
static void initCache() {
  auto &cache = GlobalIdCache::getInstance();
  // register warehouse
  cache.registForward("warehouse", &WarehouseRepository::getInternalId);
  cache.registReverse("warehouse", &WarehouseRepository::getExternalId);
  // register stock_in
  cache.registForward("stock_in", &StockInRepository::getInternalId);
  cache.registReverse("stock_in", &StockInRepository::getExternalId);
}

};

