// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>
// repos
#include <repository/warehouse/warehouse_repository.h>
// services
#include <service/warehouse/warehouse_service.h>
// tools
#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>


using namespace std::chrono;

ServiceResult WarehouseService::create(WarehouseDTO& warehouse_dto)
{
  // 检查 status 是否在范围内
  if (!utils::in(warehouse_dto.status, WarehouseDTO::status_domain)) {
    return {false, "Field status out of range"};
  }
  // 更新前初始化
  warehouse_dto.warehouse_id = utils::create_id("W-");
  warehouse_dto.created_at = time_point_cast<microseconds>(system_clock::now());
  warehouse_dto.available_capacity = warehouse_dto.capacity;

  // 插入数据到数据库
  auto insert_res = WarehouseRepository::create(warehouse_dto);

  if (!insert_res.has_value())
    return {false, "Create warehouse failed."};

  auto& cache = GlobalIdCache::getInstance();
  cache.update("warehouse", warehouse_dto.warehouse_id, insert_res.value());

  return {true};
}

ServiceResult
WarehouseService::updateByWarehouseId(const std::string& warehouse_id,
                                      const WarehouseDTO& warehouse_dto)
{
  // 检查并获取 json 内容
  auto& cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("warehouse", warehouse_dto.warehouse_id);

  if (id == 0)
    return {false, "Warehouse Not Found."};

  bool success = WarehouseRepository::updateById(id, warehouse_dto);

  if (!success)
    return {false, "Update warehouse failed."};

  return {true};
}

ServiceResult WarehouseService::getByPage(const int page, const int page_size)
{

  if (page <= 0 || page_size <= 0) {
    return {false, "Invalid page or page_size"};
  }

  // 分页查询
  auto offset = (page - 1) * page_size;

  // 获取分页数据
  count_type total = WarehouseRepository::count();
  auto warehouse_list = WarehouseRepository::getByPage(page_size, offset);

  nlohmann::json data{
    {"total", total},
    {"current_page", page},
    {"page_size", page_size},
    {"total_pages",
     static_cast<int>(std::ceil(total / static_cast<double>(page_size)))},
    {"items", warehouse_list}  // 确保每个item中的id字段已转换为string类型
  };

  return {true, "", data};
}

ServiceResult WarehouseService::setStatus(const std::string& warehouse_id,
                                          const std::string& status)
{
  if (!utils::in(status, WarehouseDTO::status_domain))
    return {false, "Status out of range."};

  auto id =
    GlobalIdCache::getInstance().getInternalId("warehouse", warehouse_id);

  if (id == 0)
    return {false, "Warehouse doesnot exists, please check your mapping."};

  auto res = WarehouseRepository::setStatus(id, status);
  if (!res)
    return {false, "Set status failed, An DB Error."};

  return {true};
}

// ServiceResult WarehouseService::getAll()
// {
//   auto warehouse_list = WarehouseRepository::getAll();
//   try {
//     json data{{"success", true},
//               {"total", warehouse_list.size()},
//               {"items", warehouse_list}};
//
//     return SET_SUC_DATA_RESPONSE(data);
//   }
//   catch (const std::exception& e) {
//     return SET_ERR_RESPONSE(500, e.what());
//   }
// }


// ServiceResult WarehouseService::removeByWarehouseId(const std::string& body)
// {
//   return utils::safeJsonExecution(body, [](const nlohmann::json& j) {
//     CHECK_REQUIRED_FIELD(j, "warehouse_id");
//     auto warehouse_id = j.at("warehouse_id").get<ex_id_type>();
//
//     auto& cache = GlobalIdCache::getInstance();
//     auto id = cache.getInternalId("warehouse", warehouse_id);
//
//     if (id == 0 || !WarehouseRepository::existsById(id))
//       return SET_ERR_RESPONSE(404, "Warehouse Not Found.");
//
//     bool success = WarehouseRepository::removeById(id);
//     return success ? SET_EMPTY_DATA_RESPONSE(200)
//                    : SET_ERR_RESPONSE(500, "DB_UPDATE_ERROR");
//   });
// }
