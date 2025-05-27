#pragma once
#include <model/dto/system/system_setting_dto.hpp>
#include <common/generic_model.hpp>

class SystemSettingRepository : public model::GenericModel<SystemSettingDTO, db::system_setting> {
public:
    // CRUD Operations
    static insert_ret_type create(const SystemSettingDTO& SystemSettingDTO);
    static select_ret_type<SystemSettingDTO> get(const std::string &system_setting_name);
    static update_ret_type updateById(const in_id_type id, const SystemSettingDTO& system_setting_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<SystemSettingDTO> getAll();
    static select_ret_type<SystemSettingDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
