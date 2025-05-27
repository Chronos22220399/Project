#include <repository/member/member_purchase_record_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type MemberPurchaseRecordRepository::create(const MemberPurchaseRecordDTO &member_purchase_record_dto) {
    return _insert(member_purchase_record_dto);
};

select_ret_type<MemberPurchaseRecordDTO> MemberPurchaseRecordRepository::get(const std::string& member_purchase_record_name) {
  return _select(db::member_purchase_record{}.member_purchase_record_name == member_purchase_record_name);
};

update_ret_type MemberPurchaseRecordRepository::update(const MemberPurchaseRecordDTO &dto) {
    return _update(dto, db::member_purchase_record{}.member_purchase_record_id == dto.member_purchase_record_id);
};

delete_ret_type MemberPurchaseRecordRepository::remove(const std::string& member_purchase_record_id) {
  return _remove(db::member_purchase_record{}.member_purchase_record_id == member_purchase_record_id);
}

// Custom Queries
select_ret_type<MemberPurchaseRecordDTO> MemberPurchaseRecordRepository::getAll() {
  return _select(db::member_purchase_record{}.id >= 0);
}

select_ret_type<MemberPurchaseRecordDTO> MemberPurchaseRecordRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::member_purchase_record{}.id >= 0, page_size, offset);
}

count_type MemberPurchaseRecordRepository::count() { return _count(); }

// 其他方法实现...
