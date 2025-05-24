#pragma once
#include <common/global_id_cache.hpp>
#include <common/include.h>

struct CacheFuncGetter {
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

  static void update(const std::string& table, const ExternalId& external_id,
                     InternalId internal_id)
  {
    return GlobalIdCache::getInstance().update(table, external_id, internal_id);
  }

  // 使缓存失效（如删除记录后调用）
  static void invalidate(const std::string& table,
                         const ExternalId& external_id)
  {
    return GlobalIdCache::getInstance().invalidate(table, external_id);
  }

  static void invalidate(const std::string& table, InternalId internal_id)
  {
    return GlobalIdCache::getInstance().invalidate(table, internal_id);
  }
};
