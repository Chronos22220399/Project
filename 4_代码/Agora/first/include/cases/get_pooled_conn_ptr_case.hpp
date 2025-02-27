//
// Created by 无铭 on 25-2-26.
//

#ifndef GET_POOLED_CONN_PTR_CASE_HPP
#define GET_POOLED_CONN_PTR_CASE_HPP

#include <Models/AdminModel.h>
#include <future>
#include <include/admin.h>
#include <sqlpp11/sqlpp11.h>
#include <utils/database_utils/database_query.hpp>
#include <utils/database_utils/database_utils.hpp>

namespace cases {
inline auto get_pooled_conn_ptr_case() {
    utils::ForLoop<168>::run([]() {
        try {
            auto pooled_conn_ptr = utils::database_utils::get_pooled_conn_ptr();
            Admin_::Admin admin;
            // auto execution =
            // (*pooled_ptr)(insert_into(admin).set(admin.username=std::to_string(i),
            // admin.password=std::to_string(i)));
            auto query = (*pooled_conn_ptr)(
                select(admin.id, admin.username, admin.password)
                    .from(admin)
                    .where(admin.id > 0));
            for (auto &row : query) {
                fmt::println("{} {}", std::string(row.username),
                             std::string(row.password));
            }
        } catch (const sqlpp::exception &e) {
            LOG("出现数据库错误: {}", e.what());
        } catch (const std::exception &e) {
            LOG("出现系统错误: {}", e.what());
        }
    });
}

// query
inline void DataBaseHelper_case_query() {
    utils::ForLoop<10>::run(
        [](int id) {
            auto query = [](auto &&pooled_conn, int id) {
                Admin_::Admin admin;
                auto result = (*pooled_conn)(select(sqlpp::all_of(admin))
                                                 .from(admin)
                                                 .where(admin.id == id));
                for (auto &row : result) {
                    fmt::println("{} {}", std::string(row.username),
                                 std::string(row.password));
                }
                return 0;
            };
            utils::database_utils::DataBaseHelper::execute<int>(query, id);
        },
        1);
}

inline void DataBaseHelper_case_update() {
    std::vector<std::future<void>> futures;
    for (size_t i = 100; i < 1000; i += 1) {
        futures.emplace_back(std::async(std::launch::async, [i] {
            utils::database_utils::DataBaseHelper::execute<int>(
                [](auto &&pooled_conn_ptr, std::string username) {
                    Admin_::Admin admin{};
                    (*pooled_conn_ptr)(update(admin)
                                           .where(admin.id == 1)
                                           .set(admin.username = username));
                    return 0;
                },
                std::to_string(i));
        }));

        for (auto &&future : futures) {
            future.wait();
        }
    }
}

inline void DataBaseHelper_case_remove() {
    std::vector<std::future<void>> futures;
    for (size_t i = 1; i < 1000; i += 1) {
        futures.emplace_back(std::async(std::launch::async, [i] {
            utils::database_utils::DataBaseHelper::execute<int>(
                [](auto &&pooled_conn_ptr, int id) {
                    Admin_::Admin admin{};
                    (*pooled_conn_ptr)(
                        remove_from(admin).where(admin.id == id));
                    return 0;
                },
                i);
        }));

        for (auto &&future : futures) {
            future.wait();
        }
    }
}

inline void AdminModel_case_create(const std::string &username,
                                   const std::string &password) {
    using namespace utils::database_utils;
    AdminModel::Admin admin{};
    admin.username = username;
    admin.password = password;
    AdminModel model{};
    auto cnt = model.create(admin);
    std::cout << cnt << std::endl;
}
} // namespace cases

#endif // GET_POOLED_CONN_PTR_CASE_HPP
