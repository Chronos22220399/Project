#include <Models/AdminModel.h>
#include <future>
#include <numeric>
#include <include/admin.h>
#include <sqlpp11/sqlpp11.h>
#include <thread>
#include <utils/database_utils/database_utils.hpp>
#include <utils/database_utils/database_query.hpp>
#include <utils/log.hpp>
#include <utils/utils.hpp>
#include <include/admin.h>
#include <cases/get_pooled_conn_ptr_case.hpp>


int main() {
    // cases::DataBaseHelper_case_update();
    // cases::DataBaseHelper_case_remove();
    // cases::AdminModel_case_create("helo", "zsh");

    AdminModel model;
    auto res = model.get_admin_by_username_test("helo");

    // for (int i = 0; i < 160; ++i) {
    //     std::vector<std::future<void>> futures;
    //     futures.emplace_back(std::async(std::launch::async, []() {
    //         const AdminModel model{};

            // std::vector<AdminModel::Admin> admins =
            //     model.get_admin_by_id_range(2, 10);
            // for (auto &admin : admins) {
            //     fmt::print("{}: {}\n", admin.id, admin.username);
            // }
    //     }));
    //
    //     for (auto &f : futures) {
    //         f.wait();
    //     }
    // }

    // Admin_::Admin admin{};
    // auto condition = (admin.id > 0);
    // GenericDataGetter<Admin> getter{};
    // auto res = getter.get_data(admin, condition);
    // for (const auto &ad : res) {
    //     fmt::print("{}\n", ad.username);
    // }

    // for (int i = 0; i < 16; ++i) {
    //   std::future res = std::async(std::launch::async, [pool_ptr]() {
    //     const AdminModel model{pool_ptr};
    //     const auto admins = model.get_admin_by_id(1);
    //     for (const auto &row : admins) {
    //       fmt::println("{}: {}\n", row.id, row.username);
    //     }
    //   });
    //   res.wait();
    // }

    // auto inserter = [](const auto &pooled_conn_ptr) {
    //   admin admin {.id=8, .username="admin", .password="admin"};
    //   Admin_::Admin adm{};
    //   (*pooled_conn_ptr)(insert_into(adm).set(adm.username=admin.username,
    //   adm.password=admin.password)); return 1;
    // };
    // DataBaseHelper::execute<int>(pool_ptr, inserter);
    return 0;
}

