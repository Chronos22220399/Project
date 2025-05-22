#pragma once
#include <common/global_id_cache.hpp>
#include <common/include.h>

struct IdGetter {
  // 转换方法
  static in_id_type getInternalId(const std::string& type,
                                  const ex_id_type& external_id)
  {
    return GlobalIdCache::getInstance().getInternalId(type, external_id);
  }

  static ex_id_type getExternalId(const std::string& type,
                                  const in_id_type& internal_id)
  {
    return GlobalIdCache::getInstance().getExternalId(type, internal_id);
  }
};
