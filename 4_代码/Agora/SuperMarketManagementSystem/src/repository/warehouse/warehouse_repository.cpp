#include <repository/warehouse/warehouse_repository.h>

// 通用 CRUD（internal）
insert_ret_type WarehouseRepository::create(const WarehouseDTO &warehouse_dto) {
  return _insert(warehouse_dto);
}

select_ret_type<WarehouseDTO> WarehouseRepository::getById(in_id_type id) {
  return _select(db::warehouse{}.id == id);
}

update_ret_type
WarehouseRepository::updateById(in_id_type id,
                                const WarehouseDTO &warehouse_dto) {
  return _update(warehouse_dto, db::warehouse{}.id == id);
}

delete_ret_type WarehouseRepository::removeById(in_id_type id) {
  return _remove(db::warehouse{}.id == id);
}

bool WarehouseRepository::existsById(in_id_type id) {
  return _exists(db::warehouse{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<WarehouseDTO>
WarehouseRepository::getByWarehouseId(const std::string &warehouse_id) {
  return _select(db::warehouse{}.warehouse_id == warehouse_id);
}

select_ret_type<WarehouseDTO>
WarehouseRepository::getByWarehouseName(const std::string &warehouse_name) {
  return _select(db::warehouse{}.warehouse_name == warehouse_name);
}

select_ret_type<WarehouseDTO>
WarehouseRepository::getByLocation(const std::string &location) {
  return _select(db::warehouse{}.location == location);
}

update_ret_type
WarehouseRepository::updateByWarehouseId(const std::string &warehouse_id,
                                         const WarehouseDTO &warehouse_dto) {
  return _update(warehouse_dto, db::warehouse{}.warehouse_id == warehouse_id);
}

delete_ret_type
WarehouseRepository::removeByWarehouseId(const std::string &warehouse_id) {
  return _remove(db::warehouse{}.warehouse_id == warehouse_id);
}

bool WarehouseRepository::existsByWarehouseId(const std::string &warehouse_id) {
  return _exists(db::warehouse{}.warehouse_id == warehouse_id);
}

bool WarehouseRepository::existsByWarehouseName(
    const std::string &warehouse_name) {
  return _exists(db::warehouse{}.warehouse_name == warehouse_name);
}

bool WarehouseRepository::existsByLocation(const std::string &location) {
  return _exists(db::warehouse{}.location == location);
}

select_ret_type<WarehouseDTO> WarehouseRepository::getAll() {
  return _select(db::warehouse{}.id >= 0);
}

select_ret_type<WarehouseDTO>
WarehouseRepository::getByPage(count_type page_size, count_type offset) {
  return _select_from(db::warehouse{}.id >= 0, page_size, offset);
}

count_type WarehouseRepository::count() { return _count(); }

// 获取 internal id 用于缓存映射
in_id_type WarehouseRepository::getInternalId(const std::string &warehouse_id) {
  auto result = utils::DataBaseHelper::execute<in_id_type>(
      [&warehouse_id](const utils::pooled_conn_ptr_type &conn_) {
        static db::warehouse warehouse{};
        auto rows =
            (*conn_)(select(warehouse.id)
                         .from(warehouse)
                         .where(warehouse.warehouse_id == warehouse_id));
        return rows.empty() ? 0 : rows.front().id;
      });
  return result;
}

// 获取 external id 用于缓存映射
std::string WarehouseRepository::getExternalId(in_id_type id) {
  auto result = utils::DataBaseHelper::execute<std::string>(
      [id](const utils::pooled_conn_ptr_type &conn_) {
        static db::warehouse warehouse{};
        auto rows = (*conn_)(select(warehouse.warehouse_id)
                                 .from(warehouse)
                                 .where(warehouse.id == id));
        return rows.empty() ? std::string() : rows.front().warehouse_id;
      });
  return result;
}
