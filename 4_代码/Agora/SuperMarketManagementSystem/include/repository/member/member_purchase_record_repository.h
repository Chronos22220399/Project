#pragma once
#include <model/dto/member/member_purchase_record_dto.hpp>
#include <common/generic_model.hpp>

class MemberPurchaseRecordRepository : public model::GenericModel<MemberPurchaseRecordDTO, db::member_purchase_record> {
public:
    // CRUD Operations
    static insert_ret_type create(const MemberPurchaseRecordDTO& MemberPurchaseRecordDTO);
    static select_ret_type<MemberPurchaseRecordDTO> get(const std::string &member_purchase_record_name);
    static update_ret_type updateById(const in_id_type id, const MemberPurchaseRecordDTO& member_purchase_record_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<MemberPurchaseRecordDTO> getAll();
    static select_ret_type<MemberPurchaseRecordDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
