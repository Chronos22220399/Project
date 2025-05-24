// third_party
#include <fmt/format.h>
// repos
#include <repository/common/unit_repository.h>
// services
#include <service/common/unit_service.h>
// tools
#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>


ServiceResult UnitService::create(const UnitDTO& unit_dto)
{
  auto& cache = GlobalIdCache::getInstance();

  if (UnitRepository::_exists(db::unit{}.unit_name == unit_dto.unit_name)) {
    return {false, "Unit name has created"};
  }

  auto id = UnitRepository::create(unit_dto);
  if (!id) {
    return {false, "Create unit failed."};
  }

  cache.update("unit", unit_dto.unit_id, id.value());
  nlohmann::json data{unit_dto};
  return {true};
}

ServiceResult UnitService::updateByUnitId(const std::string& unit_id,
                                          const UnitDTO& unit_dto)
{
  auto& cache = GlobalIdCache::getInstance();

  auto id = cache.getInternalId("unit", unit_id);

  if (id == 0) {
    return {false, "Unit not found."};
  }

  bool success = UnitRepository::updateById(id, unit_dto);
  if (!success) {
    return {false, "Update unit failed"};
  }

  return {true};
}

ServiceResult UnitService::removeByUnitId(const std::string& unit_id)
{
  auto& cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("unit", unit_id);

  if (id == 0) {
    return {false, "Unit not found."};
  }

  bool success = UnitRepository::removeById(id);
  if (!success) {
    return {false, "Remove unit failed."};
  }

  cache.invalidate("unit", unit_id);
  return {true};
}

ServiceResult UnitService::getByPage(const int page, const int page_size)
{
  if (page <= 0 || page_size <= 0) {
    return {false, "Invalid page or page_size"};
  }

  // 分页查询
  auto offset = (page - 1) * page_size;

  // 获取分页数据
  count_type total = UnitRepository::count();
  auto unit_list = UnitRepository::getByPage(page_size, offset);

  nlohmann::json data{
    {"total", total},
    {"current_page", page},
    {"page_size", page_size},
    {"total_pages",
     static_cast<int>(std::ceil(total / static_cast<double>(page_size)))},
    {"items", unit_list},  // 确保每个item中的id字段已转换为string类型
  };

  return {true, "", data};
}

ServiceResult UnitService::getAll()
{
  auto unit_list = UnitRepository::getAll();
  try {
    nlohmann::json data{
      {"success", true}, {"total", unit_list.size()}, {"items", unit_list}};
    return {true, "", data};
  } catch (const std::exception& e) {
    LOG("Exception occured while getting all, {}", e.what());
    return {false, e.what()};
  }
}
