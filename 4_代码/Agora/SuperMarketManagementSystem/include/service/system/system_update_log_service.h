#pragma once
#include <crow.h>
#include <model/dto/system/system_update_log_dto.hpp>
#include <string>

class SystemUpdateLogService {
  public:
  static ServiceResult create(SystemUpdateLogDTO& update_log_dto);
  static ServiceResult updateByUpdateId(const std::string& update_id,
                                        SystemUpdateLogDTO& update_lot_dto);
  static ServiceResult removeByUpdateId(const std::string& update_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
