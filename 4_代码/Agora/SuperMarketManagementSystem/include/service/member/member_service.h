#pragma once
#include <common/common_utils.hpp>
#include <crow.h>
#include <model/dto/member/member_dto.hpp>
#include <string>

class MemberService {
  public:
  static ServiceResult create(MemberDTO& dto);
  static ServiceResult updateByMemberId(const std::string& ex_id,
                                        MemberDTO& dto);
  static ServiceResult removeByMemberId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
