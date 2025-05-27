#pragma once
#include <crow.h>
#include <model/dto/member/member_level_dto.hpp>
#include <string>

class MemberLevelService {
  public:
  static ServiceResult create(MemberLevelDTO& dto);
  static ServiceResult updateByLevelId(const std::string& ex_id,
                                       MemberLevelDTO& dto);
  static ServiceResult removeByLevelId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
