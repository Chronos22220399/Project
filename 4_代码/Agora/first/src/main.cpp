#include <Models/AdminModel.h>
#include <cases/get_pooled_conn_ptr_case.hpp>
#include <crow.h>
#include <future>
#include <include/admin.h>
#include <numeric>
#include <sqlpp11/sqlpp11.h>
#include <string>
#include <thread>
#include <utils/database_utils/database_query.hpp>
#include <utils/database_utils/database_utils.hpp>
#include <utils/log.hpp>
#include <utils/utils.hpp>

// template <typename TableRow, typename RowValueType> struct DataGetter;
// template <typename Table, typename RowValueType> struct DataSetter;
//
// template <typename TableType, typename RowValueType>
// struct GenericDBOperation : utils::database_utils::DataBaseHelper {
//     // 通用查询
//     template <typename ColumnPtr, typename Value>
//     [[nodiscard]] std::vector<RowValueType>
//     get_table_generic_by(Value &&value) const {
//         using pooled_conn_ptr_type =
//             utils::database_utils::ConnDefiner::pooled_conn_ptr_type;
//         auto query = [](const pooled_conn_ptr_type &conn, Value &&value_) {
//             TableType table;
//             ColumnPtr column_ptr{};
//             auto res = (*conn)(
//                 select(all_of(table))
//                     .from(table)
//                     .where(table.*column_ptr ==
//                     std::forward<Value>(value_)));
//             std::vector<RowValueType> ret{};
//             for (const auto &row : res) {
//                 std::string username = row.username;
//                 ret.push_back(
//                     DataGetter<decltype(row), RowValueType>::get_row_value(
//                         row));
//             }
//             return ret;
//         };
//         return execute<std::vector<RowValueType>>(query,
//                                                   std::forward<Value>(value));
//     }
//
//     // 通用创建
//     auto generic_create(RowValueType &&row_value) const {
//         auto creater = [](const pooled_conn_ptr_type &conn,
//                           RowValueType &&row_value_) {
//             TableType table;
//             auto res = (*conn)(
//                 insert_into(table).set(DataSetter<TableType,
//                 RowValueType>::set(
//                     std::forward<TableType>(table),
//                     std::forward<RowValueType>(row_value_))));
//             return 1;
//         };
//         return execute<size_t>(creater,
//         std::forward<RowValueType>(row_value));
//     }
// };
//

// template <typename TableRow> struct DataGetter<TableRow, Admin> {
//     static Admin get_row_value(TableRow &&row) {
//         return Admin{.id = size_t(row.id),
//                      .username = row.username,
//                      .password = row.password};
//     }
// };
//
// template <typename Table> struct DataSetter<Table, Admin> {
//     static auto set(Table &&table, const Admin &admin) {
//         return std::make_tuple(table.username = admin.username,
//                                table.username = admin.password);
//     }
// };

struct Admin {
    size_t id;
    std::string username;
    std::string password;
};

template <typename Model, typename Table>
struct ModelReflectTable;

// 特化出从模型到表的反射
template <>
struct ModelReflectTable<Admin, Admin_::Admin> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&Admin::id, &Admin_::Admin::id),
        std::make_pair(&Admin::username, &Admin_::Admin::username),
        std::make_pair(&Admin::password, &Admin_::Admin::password)
    );
};

template <typename Reflect, typename Model, typename Table, size_t ...Is>
auto make_assignments_impl(Model &&model, Table &&table, std::index_sequence<Is...>) {
    return std::make_tuple(
        (table.*std::get<Is>(Reflect::map_members).second = model.*std::get<Is>(Reflect::map_members).first)...
    );
}

template <typename Reflect, typename Model, typename Table>
auto make_assignments(Model &&model, Table &&table) {
    constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
    return make_assignments_impl<Reflect, Model, size>(model, table, std::make_index_sequence<size>{});
}


int main() {
    // GenericDBOperation<Admin_::Admin, Admin> getter{};
    // Admin_::Admin ad;

    // getter.generic_create(Admin{.username = "heelo", .password = "asdf"});
    // auto res =
    //     getter.get_table_generic_by<decltype(&Admin_::Admin::username)>("helo");
    // for (auto &admin : res) {
    //     fmt::println("{} {} {}", admin.id, admin.username, admin.password);
    // }

    // crow::SimpleApp app{};
    // CROW_ROUTE(app, "/get_all_admins")([]() {
    //     AdminModel model{};
    //     auto admins = model.get_all_admins();
    //     std::string ret = "";
    //     for (const auto &admin : admins) {
    //         ret += admin.username + "\r\n";
    //     }
    //     return ret;
    // });
    //
    // CROW_ROUTE(app, "/get_admin_by_id/<int>")([](size_t id) {
    //     AdminModel model{};
    //     auto admins = model.get_admin_by_id(id);
    //     std::string ret = "";
    //     for (const auto &admin : admins) {
    //         ret += admin.username + "\r\n";
    //     }
    //     return ret;
    // });
    //
    // CROW_ROUTE(app,
    //            "/get_admin_by_username/<string>")([](std::string username) {
    //     AdminModel model{};
    //     auto admins = model.get_admin_by_username(username);
    //     std::string ret = "";
    //     for (const auto &admin : admins) {
    //         ret += admin.username + "\r\n";
    //     }
    //     return ret;
    // });
    //
    // app.port(18080).multithreaded().run();

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
