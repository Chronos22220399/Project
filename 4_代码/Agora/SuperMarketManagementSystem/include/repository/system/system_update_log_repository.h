#pragma once
#include <model/dto/system/system_update_log_dto.hpp>
#include <common/generic_model.hpp>

class SystemUpdateLogRepository : public model::GenericModel<SystemUpdateLogDTO, db::system_update_log> {
public:
    // CRUD Operations
    static insert_ret_type create(const SystemUpdateLogDTO& SystemUpdateLogDTO);
    static select_ret_type<SystemUpdateLogDTO> get(const std::string &system_update_log_name);
    static update_ret_type updateById(const in_id_type id, const SystemUpdateLogDTO& system_update_log_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<SystemUpdateLogDTO> getAll();
    static select_ret_type<SystemUpdateLogDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
