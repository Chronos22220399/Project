#pragma once
#include <model/dto/system/permission_dto.hpp>
#include <common/generic_model.hpp>

class PermissionRepository : public model::GenericModel<PermissionDTO, db::permission> {
public:
    // CRUD Operations
    static insert_ret_type create(const PermissionDTO& PermissionDTO);
    static select_ret_type<PermissionDTO> get(const std::string &permission_name);
    static update_ret_type updateById(const in_id_type id, const PermissionDTO& permission_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<PermissionDTO> getAll();
    static select_ret_type<PermissionDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
