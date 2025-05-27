#pragma once
#include <model/dto/employee/position_dto.hpp>
#include <common/generic_model.hpp>

class PositionRepository : public model::GenericModel<PositionDTO, db::position> {
public:
    // CRUD Operations
    static insert_ret_type create(const PositionDTO& PositionDTO);
    static select_ret_type<PositionDTO> get(const std::string &position_name);
    static update_ret_type updateById(const in_id_type id, const PositionDTO& position_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<PositionDTO> getAll();
    static select_ret_type<PositionDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
