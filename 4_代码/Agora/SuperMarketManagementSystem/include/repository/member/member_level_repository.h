#pragma once
#include <common/generic_model.hpp>
#include <model/dto/member/member_level_dto.hpp>

class MemberLevelRepository
  : public model::GenericModel<MemberLevelDTO, db::member_level> {
  public:
  // CRUD Operations
  static insert_ret_type create(const MemberLevelDTO& MemberLevelDTO);
  static select_ret_type<MemberLevelDTO>
  get(const std::string& member_level_name);
  static update_ret_type updateById(const in_id_type id,
                                    const MemberLevelDTO& member_level_dto);
  static delete_ret_type removeById(const in_id_type id);

  // Custom Queries
  static select_ret_type<MemberLevelDTO> getAll();
  static select_ret_type<MemberLevelDTO> getByPage(int page_size, int offset);
  static count_type count();


  // Foreign Key Relations
};
