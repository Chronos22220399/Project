#pragma once
#include <model/dto/member/member_dto.hpp>
#include <common/generic_model.hpp>

class MemberRepository : public model::GenericModel<MemberDTO, db::member> {
public:
    // CRUD Operations
    static insert_ret_type create(const MemberDTO& MemberDTO);
    static select_ret_type<MemberDTO> get(const std::string &member_name);
    static update_ret_type update(const MemberDTO& member_dto);
    static delete_ret_type remove(const std::string &member_id);
    
    // Custom Queries
    static select_ret_type<MemberDTO> getAll();
    static select_ret_type<MemberDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
