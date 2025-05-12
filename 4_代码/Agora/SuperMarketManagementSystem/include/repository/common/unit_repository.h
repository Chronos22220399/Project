#pragma once
#include <common/generic_model.hpp>
#include <model/dto/common/unit_dto.hpp>

class UnitRepository : public model::GenericModel<UnitDTO, db::unit> {
public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const UnitDTO &unit_dto);
  static select_ret_type<UnitDTO> getById(in_id_type id);
  static update_ret_type updateById(in_id_type id, const UnitDTO &unit_dto);
  static delete_ret_type removeById(in_id_type id);
  static bool existsById(in_id_type id);

  // 面向业务 CRUD（external）
  static select_ret_type<UnitDTO> getByUnitId(const std::string &unit_id);
  static select_ret_type<UnitDTO> getByName(const std::string &unit_name);
  static update_ret_type updateByUnitId(const std::string &unit_id,
                                        const UnitDTO &unit_dto);
  static delete_ret_type removeByUnitId(const std::string &unit_id);
  static bool existsByUnitId(const std::string &unit_id);

  // other
  static select_ret_type<UnitDTO> getAll();
  static select_ret_type<UnitDTO> getByPage(count_type page_size,
                                            count_type offset);
  static count_type count();

  static in_id_type getInternalId(const ex_id_type &unit_id);
  static ex_id_type getExternalId(in_id_type id);
};
