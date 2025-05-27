#pragma once
#include <common/common_utils.hpp>
#include <crow.h>
#include <model/dto/member/member_dto.hpp>
#include <string>

class MemberService {
  public:
  static ServiceResult create(MemberDTO& dto);
  static ServiceResult updateByMemberId(const ex_id_type& ex_id,
                                        MemberDTO& dto);
  static ServiceResult removeByMemberId(const ex_id_type& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();

  // 注销会员
  static ServiceResult invalidMemberByMember(const ex_id_type& member_id);
};
