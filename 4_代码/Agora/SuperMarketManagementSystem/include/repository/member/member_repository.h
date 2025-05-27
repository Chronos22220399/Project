#pragma once
#include <common/generic_model.hpp>
#include <model/dto/member/member_dto.hpp>

class MemberRepository : public model::GenericModel<MemberDTO, db::member> {
  public:
  // CRUD Operations
  static insert_ret_type create(const MemberDTO& MemberDTO);
  static select_ret_type<MemberDTO> get(const std::string& member_name);
  static update_ret_type updateById(const in_id_type id,
                                    const MemberDTO& member_dto);
  static delete_ret_type removeById(const in_id_type id);

  // Custom Queries
  static select_ret_type<MemberDTO> getAll();
  static select_ret_type<MemberDTO> getByPage(int page_size, int offset);
  static count_type count();

  static std::optional<in_id_type>
  findMemberByUserRKId(const in_id_type& user_rk_id);
  // Foreign Key Relations
};
