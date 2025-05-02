#pragma once
#include <model/dto/goods/goods_dto.hpp>

class GoodsRepository : protected model::GenericModel<GoodsDTO, db::goods> {
public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const GoodsDTO &goods_dto);
  static select_ret_type<GoodsDTO> getById(id_type id);
  static update_ret_type updateByGoodsId(id_type id, const GoodsDTO &goods_dto);
  static delete_ret_type removeById(id_type id);
  static bool existsById(id_type id);

  // 面向业务 CRUD（external）
  static select_ret_type<GoodsDTO> getByGoodsId(const std::string &goods_id);
  static select_ret_type<GoodsDTO> getByName(const std::string &goods_name);
  static update_ret_type updateByGoodsId(const std::string &goods_id,
                                         const GoodsDTO &goods_dto);
  static delete_ret_type removeByGoodsId(const std::string &goods_id);
  static bool existsByGoodsId(const std::string &goods_id);

  // other
  static select_ret_type<GoodsDTO> getAll();
  static select_ret_type<GoodsDTO> getByPage(count_type page_size,
                                             count_type offset);
  static count_type count();

  // 多表查询商品详细信息
  static select_ret_type<GoodsDetailInfo>
  getGoodsDetailInfoByGoodsId(const std::string &goods_id);

  // 获取 internal id 用于缓存正向映射
  static id_type getInternalId(const std::string &goods_id);
  // 获取 external id 用于缓存逆向映射
  static std::string getExternalId(id_type id);
};
