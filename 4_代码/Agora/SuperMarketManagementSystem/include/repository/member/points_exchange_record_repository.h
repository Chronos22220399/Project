#pragma once
#include <model/dto/member/points_exchange_record_dto.hpp>
#include <common/generic_model.hpp>

class PointsExchangeRecordRepository : public model::GenericModel<PointsExchangeRecordDTO, db::points_exchange_record> {
public:
    // CRUD Operations
    static insert_ret_type create(const PointsExchangeRecordDTO& PointsExchangeRecordDTO);
    static select_ret_type<PointsExchangeRecordDTO> get(const std::string &points_exchange_record_name);
    static update_ret_type updateById(const in_id_type id, const PointsExchangeRecordDTO& points_exchange_record_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<PointsExchangeRecordDTO> getAll();
    static select_ret_type<PointsExchangeRecordDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
