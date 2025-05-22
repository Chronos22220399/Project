#pragma once
#include <crow.h>
#include <string>

class StockInService {
public:
    static crow::response create({} &dto);
static crow::response update(const std::string &ex_id, {} &dto);
static crow::response remove(const std::string &ex_id);
static crow::response getByPage(const int page, const int page_size);
static crow::response getAll();
};
