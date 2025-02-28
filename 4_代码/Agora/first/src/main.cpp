#include <crow.h>
#include <include/admin.h>
#include <sqlpp11/sqlpp11.h>
#include <string>
#include <utils/database_utils/database_utils.hpp>

struct Admin {
    size_t id;
    std::string username;
    std::string password;
};

template <typename Model, typename Table>
struct ReflectTable;

template <typename Model, typename TableRow>
struct ReflectTableRow {};



namespace details {
    template <size_t N, size_t ...Is>
    auto make_index_sequence_from(std::index_sequence<Is...>) {
        return std::index_sequence<N+Is...>{};
    }

    template <size_t N, size_t L>
    auto make_index_sequence_from() {
        return make_index_sequence_from<N>(std::make_index_sequence<L>{});
    }

    template <typename Reflect, typename Model, typename Table, size_t ...Is>
    auto assign_table_impl(Model &&model, Table &&table, std::index_sequence<Is...>) {
        return std::make_tuple(
            (table.*std::get<Is>(Reflect::map_members).second = model.*std::get<Is>(Reflect::map_members).first)...
        );
    }

    template <typename Reflect, typename Model, typename Table, size_t ...Is>
    auto assign_table_impl(const Model &model, const Table &table, std::index_sequence<Is...>) {
        return std::make_tuple(
            (table.*std::get<Is>(Reflect::map_members).second = model.*std::get<Is>(Reflect::map_members).first)...
        );
    }

    template <typename Reflect, typename Model, typename Table, size_t Start = 1>
    auto assign_table(Model &&model, Table &&table) {
        constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
        return assign_table_impl<Reflect>(std::forward<Model>(model), std::forward<Table>(table),
                                              details::make_index_sequence_from<Start, size - Start>());
    }

    template <typename Reflect, typename Model, typename Table, size_t ...Is>
    Model assign_model_impl(Table &&table, std::index_sequence<Is...>) {
        Model model;
        ((model.*std::get<Is>(Reflect::map_members).first = table.*std::get<Is>(Reflect::map_members).second), ...);
        return model;
    }

    template <typename Reflect, typename Model, typename Table, size_t ...Is>
    Model assign_model_impl(const Table &table, std::index_sequence<Is...>) {
        Model model;
        ((model.*std::get<Is>(Reflect::map_members).first = table.*std::get<Is>(Reflect::map_members).second), ...);
        return model;
    }

    template <typename Reflect, typename Model, typename Table, size_t Start = 1>
    Model assign_model_impl(Table &&table) {
        constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
        return assign_model_impl<Reflect, Model, Table, Start>(std::forward<Table>(table));
    }
}


template <typename Model, typename Table, size_t Start = 1>
class GenericRepository {
    using Reflect = ReflectTable<Model, Table>;
    using pooled_conn_ptr_type = std::shared_ptr<sqlpp::sqlite3::pooled_connection>;
    using SelectRetType = std::vector<Model>;
    using InsertRetType = bool;
    using UpdateRetType = bool;
    using DeleteRetType = bool;
public:
    InsertRetType insert(const Model &model) const {
        return utils::database_utils::DataBaseHelper::execute<InsertRetType>([](const pooled_conn_ptr_type &conn, const Model &model_) {
            Table table {};
            (*conn)(insert_into(table).set(details::assign_table<Reflect, Model, Table, Start>(model_, table)));
            return true;
        }, model);
    }

    template <typename Condition>
    UpdateRetType update(const Model& model, const Condition& condition) const {
        return utils::database_utils::DataBaseHelper::execute<UpdateRetType>([] (const pooled_conn_ptr_type &conn_, const Model &model_, const Condition &condition_) {
            Table table {};
            (*conn_)(sqlpp::update(table).set(details::assign_table<Reflect, Model, Table, Start>(model_, table)).where(
                condition_));
            return true;
        }, model, condition);
    }

    template <typename Condition>
    SelectRetType select(const Condition &condition) const {
        return utils::database_utils::DataBaseHelper::execute<SelectRetType>([] (const pooled_conn_ptr_type &conn_, const Condition &condition_) {
            Table table {};
            SelectRetType ret_container {};
            auto select_result = (*conn_)(sqlpp::select(all_of(table)).from(table).where(condition_));
            for (auto &row : select_result) {
                ret_container.push_back(ReflectTableRow<Admin, decltype(row)>::assign_model(row));
            }
            return ret_container;
        }, condition);
    }

    template <typename Condition>
    DeleteRetType remove(const Condition &condition) const {
        return utils::database_utils::DataBaseHelper::execute<DeleteRetType>([] (const pooled_conn_ptr_type &conn_, const Condition &condition_) {
            Table table {};
            (*conn_)(remove_from(table).where(condition_));
            return true;
        }, condition);
    }
};

// 特化出从模型到表的反射
template <>
struct ReflectTable<Admin, Admin_::Admin> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&Admin::id, &Admin_::Admin::id),
        std::make_pair(&Admin::username, &Admin_::Admin::username),
        std::make_pair(&Admin::password, &Admin_::Admin::password)
    );
};

template <typename AdminTableRow>
struct ReflectTableRow <Admin, AdminTableRow> {
    static constexpr auto assign_model(AdminTableRow && row) {
        return Admin {.id = static_cast<size_t>(row.id), .username = row.username, .password = row.password};
    }
};

int main() {
    GenericRepository<Admin, Admin_::Admin> repository;
    for (size_t i = 60; i < 70; ++i) {
        Admin admin {.username = std::to_string(i + 30), .password = "password"};
        // repository.insert(Admin{.username = std::to_string(i), .password = std::to_string(i)});
        repository.remove(Admin_::Admin{}.username == std::to_string(i));
        // repository.update(admin, Admin_::Admin{}.username == std::to_string(i));
    }
    auto rows = repository.select(Admin_::Admin{}.id >= 44);
    for (auto &row : rows) {
        std::cout << row.id << " " << row.username << " " << row.password << std::endl;
    }

    // auto res = repository.select(Admin_::Admin{}.id == 43);
    // for (auto &row : res) {
    //     std::cout << row.id << " " << row.username << std::endl;
    // }
    // repository.update(admin, Admin_::Admin{}.id == 43);

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

    return 0;
}