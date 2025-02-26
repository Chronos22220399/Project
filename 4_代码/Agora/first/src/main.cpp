#include <Models/AdminModel.h>
#include <future>
#include <include/admin.h>
#include <sqlpp11/sqlpp11.h>
#include <thread>
#include <utils/database_utils/database_utils.hpp>
#include <utils/database_utils/database_query.hpp>
#include <utils/log.hpp>
#include <utils/utils.hpp>

struct Admin {
    int id;
    std::string username;
    std::string password;
    Admin() = default;
    Admin(const int id_, std::string username_, std::string password_)
        : id(id_), username(std::move(username_)),
          password(std::move(password_)) {}
};

template <typename TableRow> struct utils::database_utils::DataTypeTraits<TableRow, Admin> {
    static Admin get_args(const TableRow &row) {
        return Admin(row.id, row.username, row.password);
    }
};

int main() {
    auto dir = std::filesystem::current_path();
    auto pool_ptr = utils::database_utils::get_conn_pool_ptr();
    auto pooled_conn = pool_ptr->get();

    // Admin_::Admin admin{};
    // auto condition = (admin.id > 0);
    // utils::GenericDataGetter<Admin> getter{};
    // auto res = getter.get_data(pool_ptr, admin, condition);
    // for (const auto &ad : res) {
    //     fmt::print("{}\n", ad.username);
    // }

    for (int i = 0; i < 160; ++i) {
        std::future res = std::async(std::launch::async, [pool_ptr]() {
            const AdminModel model{pool_ptr};
            std::vector<AdminModel::Admin> admins =
                model.get_admin_by_id_range(2, 10);
            for (auto &admin : admins) {
                fmt::print("{}: {}\n", admin.id, admin.username);
            }
        });
        res.wait();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
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
