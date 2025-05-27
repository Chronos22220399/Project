#pragma once
#include <model/dto/member/points_policy_dto.hpp>
#include <common/generic_model.hpp>

class PointsPolicyRepository : public model::GenericModel<PointsPolicyDTO, db::points_policy> {
public:
    // CRUD Operations
    static insert_ret_type create(const PointsPolicyDTO& PointsPolicyDTO);
    static select_ret_type<PointsPolicyDTO> get(const std::string &points_policy_name);
    static update_ret_type updateById(const in_id_type id, const PointsPolicyDTO& points_policy_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<PointsPolicyDTO> getAll();
    static select_ret_type<PointsPolicyDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
