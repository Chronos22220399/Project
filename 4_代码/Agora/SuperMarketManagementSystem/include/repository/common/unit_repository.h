#pragma once
#include <model/dto/common/unit_dto.hpp>
#include <common/generic_model.hpp>

class UnitRepository : protected model::GenericModel<UnitDTO, db::unit> {
public:
    // CRUD Operations
    static insert_ret_type create(const UnitDTO& UnitDTO);
    static select_ret_type<UnitDTO> get(id_type id);
    static update_ret_type update(const UnitDTO& unit_dto);
    static delete_ret_type remove(id_type id);
    
    // Custom Queries
    static select_ret_type<UnitDTO> getAll();
    static select_ret_type<UnitDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    // Foreign Key Relations
    
};
