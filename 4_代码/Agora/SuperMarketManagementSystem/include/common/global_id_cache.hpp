#pragma once
// tools
#include <common/database_utils.hpp>
#include <common/uni_define.h>
// third_party
#include <fmt/format.h>
#include <sqlpp11/sqlpp11.h>
// stl
#include <mutex>
#include <string>
#include <unordered_map>
// repository
#include <repository/goods/goods_repository.h>
#include <repository/warehouse/warehouse_repository.h>

class GlobalIdCache {
  using TableName = std::string;
  using ExternalId = std::string;
  using InternalId = id_type;

  std::mutex mtx_;
  // 正向缓存：external_id → internal_id
  std::unordered_map<TableName, std::unordered_map<ExternalId, InternalId>> forward_cache_;
  // 反向缓存：internal_id → external_id
  std::unordered_map<TableName, std::unordered_map<InternalId, ExternalId>> reverse_cache_;
  
  // 查询函数映射
  inline static std::unordered_map<TableName, std::function<InternalId(const ExternalId&)>> forward_selecters_;
  inline static std::unordered_map<TableName, std::function<ExternalId(InternalId)>> reverse_selecters_;

  GlobalIdCache() = default;

public:
  GlobalIdCache(const GlobalIdCache&) = delete;
  GlobalIdCache& operator=(const GlobalIdCache&) = delete;

  static GlobalIdCache& getInstance() {
    static GlobalIdCache instance;
    return instance;
  }

  // 注册正向查询函数（external_id → internal_id）
  static void registForward(const std::string& table,
                           std::function<InternalId(const ExternalId&)> selecter) {
    forward_selecters_[table] = std::move(selecter);
  }

  // 注册反向查询函数（internal_id → external_id）
  static void registReverse(const std::string& table,
                           std::function<ExternalId(InternalId)> selecter) {
    reverse_selecters_[table] = std::move(selecter);
  }

  // 通过 external_id 获取 internal_id
  InternalId getInternalId(const std::string& table, const ExternalId& external_id) {
    std::lock_guard<std::mutex> lock(mtx_);

    // 检查正向缓存
    auto& table_cache = forward_cache_[table];
    if (auto it = table_cache.find(external_id); it != table_cache.end()) {
      return it->second;
    }

    // 查询数据库
    if (auto it = forward_selecters_.find(table); it != forward_selecters_.end()) {
      InternalId internal_id = it->second(external_id);
      if (internal_id != 0) {
        // 更新双向缓存
        table_cache[external_id] = internal_id;
        reverse_cache_[table][internal_id] = external_id;
      }
      return internal_id;
    } else {
      std::cerr << "No forward selector for table: " << table << std::endl;
      return 0;
    }
  }

  // 通过 internal_id 获取 external_id
  ExternalId getExternalId(const std::string& table, InternalId internal_id) {
    std::lock_guard<std::mutex> lock(mtx_);

    // 检查反向缓存
    auto& table_reverse_cache = reverse_cache_[table];
    if (auto it = table_reverse_cache.find(internal_id); it != table_reverse_cache.end()) {
      return it->second;
    }

    // 查询数据库
    if (auto it = reverse_selecters_.find(table); it != reverse_selecters_.end()) {
      ExternalId external_id = it->second(internal_id);
      if (!external_id.empty()) {
        // 更新双向缓存
        table_reverse_cache[internal_id] = external_id;
        forward_cache_[table][external_id] = internal_id;
      }
      return external_id;
    } else {
      std::cerr << "No reverse selector for table: " << table << std::endl;
      return "";
    }
  }

  // 手动更新双向缓存（如新增记录后调用）
  void update(const std::string& table, const ExternalId& external_id, InternalId internal_id) {
    std::lock_guard<std::mutex> lock(mtx_);
    forward_cache_[table][external_id] = internal_id;
    reverse_cache_[table][internal_id] = external_id;
  }

  // 使缓存失效（如删除记录后调用）
  void invalidate(const std::string& table, const ExternalId& external_id) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (auto it = forward_cache_[table].find(external_id); it != forward_cache_[table].end()) {
      InternalId internal_id = it->second;
      forward_cache_[table].erase(external_id);
      reverse_cache_[table].erase(internal_id);
    }
  }

  void invalidate(const std::string& table, InternalId internal_id) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (auto it = reverse_cache_[table].find(internal_id); it != reverse_cache_[table].end()) {
      ExternalId external_id = it->second;
      reverse_cache_[table].erase(internal_id);
      forward_cache_[table].erase(external_id);
    }
  }
};
