//
// Created by 无铭 on 25-5-22.
//
#pragma once
#include <common/global_id_cache.hpp>
#include <repository/goods/goods_category_repository.h>
#include <repository/goods/promotion_repository.h>
#include <repository/goods/goods_repository.h>

namespace goods {
static void initCache() {
  auto &cache = GlobalIdCache::getInstance();
  // register goods
  cache.registForward("goods", &GoodsRepository::getInternalId);
  cache.registReverse("goods", &GoodsRepository::getExternalId);
  // register goods_category
  cache.registForward("goods_category", &GoodsCategoryRepository::getInternalId);
  cache.registReverse("goods_category", &GoodsCategoryRepository::getExternalId);
  // register promotion
  cache.registForward("promotion", &PromotionRepository::getInternalId);
  cache.registReverse("promotion", &PromotionRepository::getExternalId);
}

};

