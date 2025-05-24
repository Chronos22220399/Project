//
// Created by 无铭 on 25-5-22.
//

#pragma once
#include <common/global_id_cache.hpp>
#include <repository/common/unit_repository.h>

namespace common {
static void initCache() {
  auto &cache = GlobalIdCache::getInstance();
  // register unit
  cache.registForward("unit", &UnitRepository::getInternalId);
  cache.registReverse("unit", &UnitRepository::getExternalId);
}

};