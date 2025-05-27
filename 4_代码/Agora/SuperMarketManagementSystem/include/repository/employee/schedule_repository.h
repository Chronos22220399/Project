#pragma once
#include <model/dto/employee/schedule_dto.hpp>
#include <common/generic_model.hpp>

class ScheduleRepository : public model::GenericModel<ScheduleDTO, db::schedule> {
public:
    // CRUD Operations
    static insert_ret_type create(const ScheduleDTO& ScheduleDTO);
    static select_ret_type<ScheduleDTO> get(const std::string &schedule_name);
    static update_ret_type updateById(const in_id_type id, const ScheduleDTO& schedule_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<ScheduleDTO> getAll();
    static select_ret_type<ScheduleDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
