#include <repository/member/points_exchange_record_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type PointsExchangeRecordRepository::create(const PointsExchangeRecordDTO &points_exchange_record_dto) {
    return _insert(points_exchange_record_dto);
};

select_ret_type<PointsExchangeRecordDTO> PointsExchangeRecordRepository::get(const std::string& points_exchange_record_name) {
  return _select(db::points_exchange_record{}.points_exchange_record_name == points_exchange_record_name);
};

update_ret_type PointsExchangeRecordRepository::update(const PointsExchangeRecordDTO &dto) {
    return _update(dto, db::points_exchange_record{}.points_exchange_record_id == dto.points_exchange_record_id);
};

delete_ret_type PointsExchangeRecordRepository::remove(const std::string& points_exchange_record_id) {
  return _remove(db::points_exchange_record{}.points_exchange_record_id == points_exchange_record_id);
}

// Custom Queries
select_ret_type<PointsExchangeRecordDTO> PointsExchangeRecordRepository::getAll() {
  return _select(db::points_exchange_record{}.id >= 0);
}

select_ret_type<PointsExchangeRecordDTO> PointsExchangeRecordRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::points_exchange_record{}.id >= 0, page_size, offset);
}

count_type PointsExchangeRecordRepository::count() { return _count(); }

// 其他方法实现...
