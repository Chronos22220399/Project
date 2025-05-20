#pragma once
// stl
#include <string>
// third_party
#include <crow.h>
// tools
#include <common/common_utils.hpp>
#include <common/uni_define.h>
// repo
#include <repository/goods/goods_category_repository.h>

class GoodsCategoryService {
  public:
  static ServiceResult create(const GoodsCategoryDTO& gc_dto);

  static ServiceResult getAll();
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getByGoodsCategoryId(const std::string& body);

  static ServiceResult removeByGoodsCategoryId(const std::string& body);

  static ServiceResult
  updateByGoodsCategoryId(const std::string& goods_category_id,
                          const GoodsCategoryDTO& gc_dto);
};
