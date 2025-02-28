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
    auto from_model_impl(Model &&model, Table &&table, std::index_sequence<Is...>) {
        return std::make_tuple(
            (table.*std::get<Is>(Reflect::map_members).second = model.*std::get<Is>(Reflect::map_members).first)...
        );
    }

    template <typename Reflect, typename Model, typename Table, size_t Start = 1>
    auto from_model(const Model &model, const Table &table) {
        constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
        return from_model_impl<Reflect>(model, table, details::make_index_sequence_from<Start, size-Start>());
    }

    template <typename Reflect, typename Model, typename Table, size_t Start = 1>
    auto from_model(Model &&model, Table &&table) {
        constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
        return from_model_impl<Reflect>(std::forward<Model>(model), std::forward<Table>(table),
                                              details::make_index_sequence_from<Start, size - Start>());
    }

    template <typename Reflect, typename Model, typename Table, size_t ...Is>
    Model to_model_impl(Table &&table, std::index_sequence<Is...>) {
        Model model;
        ((model.*std::get<Is>(Reflect::map_members).first = table.*std::get<Is>(Reflect::map_members).second), ...);
        return model;
    }

    template <typename Reflect, typename Model, typename Table, size_t Start = 1>
    Model to_model(Table &&table) {
        constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
        return to_model_impl<Reflect, Model, Table, Start>(std::forward<Table>(table));
    }

    template <typename Reflect, typename Model, typename Table, size_t Start = 1>
    Model to_model(const Table &table) {
        constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
        return to_model_impl<Reflect, Model, Table, Start>(table);
    }
}


template <typename Model, typename Table, size_t Start = 1>
class GenericRepository {
    using Reflect = ModelReflectTable<Model, Table>;
    using pooled_conn_ptr_type = std::shared_ptr<sqlpp::sqlite3::pooled_connection>;
    using RetContainer = std::vector<Model>;
public:
    bool insert(Model&& model) {
        return utils::database_utils::DataBaseHelper::execute<bool>([](const pooled_conn_ptr_type &conn, Model &&model_) {
            Table table {};
            (*conn)(insert_into(table).set(details::from_model<Reflect, Start>(model_, table)));
        }, std::forward<Model>(model));
    }

    bool insert(const Model& model) {
        return utils::database_utils::DataBaseHelper::execute<bool>([](const pooled_conn_ptr_type &conn_, const Model &model_) {
            Table table {};
            (*conn_)(insert_into(table).set(details::from_model<Reflect, Model, Table, Start>(model_, table)));
            return true;
        }, model);
    }

    template <typename Condition>
    bool update(Model&& model, Condition&& condition) {
        return utils::database_utils::DataBaseHelper::execute<bool>([] (const pooled_conn_ptr_type &conn_, Model &&model_, Condition &&condition_) {
            Table table {};
            (*conn_)(sqlpp::update(table).set(details::from_model<Reflect, Model, Table, Start>(model_, table)).where(
                std::forward<Condition>(condition_)));
            return true;
        }, std::forward<Model>(model), std::forward<Condition>(condition));
    }

    template <typename Condition>
    bool update(const Model& model, Condition&& condition) {
        return utils::database_utils::DataBaseHelper::execute<bool>([] (const pooled_conn_ptr_type &conn_, const Model &model_, Condition &&condition_) {
            Table table {};
            (*conn_)(sqlpp::update(table).set(details::from_model<Reflect, Model, Table, Start>(model_, table)).where(std::forward<Condition>(condition_)));
            return true;
        }, model, std::forward<Condition>(condition));
    }

    template <typename Condition>
    RetContainer select(Condition &&condition = {}) {
        return utils::database_utils::DataBaseHelper::execute<RetContainer>([] (const pooled_conn_ptr_type &conn_, Condition &&condition_) {
            Table table {};
            RetContainer ret_container {};
            auto select_result = (*conn_)(sqlpp::select(all_of(table)).from(table).where(std::forward<Condition>(condition_)));
            for (auto &row : select_result) {
                ret_container.push_back(details::to_model<Reflect, Model, Table, Start>(row));
            }
            return ret_container;
        }, std::forward<Condition>(condition));
    }
};


int main() {

    using Reflect = ModelReflectTable<Admin, Admin_::Admin>;
    auto conn_ = utils::database_utils::get_pooled_conn_ptr();
    using namespace std;
    // cin >> admin.username >> admin.password;
    GenericRepository<Admin, Admin_::Admin, 1> repository;
    repository.select(Admin_::Admin{}.id >= 0);
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

// template <typename Model, typename Table>
// class GenericRepository {
//     using Reflect = ModelReflectTable<Model, Table>;
//     using pooled_conn_ptr_type = utils::database_utils::ConnDefiner::pooled_conn_ptr_type;
//
// public:
//     GenericRepository() = default;
//     ~GenericRepository() = default;
//
//     bool insert(const Model& model) {
//         return utils::database_utils::DataBaseHelper::execute<bool>([] (const pooled_conn_ptr_type &conn, Model &&_model) {
//             Table table;
//             (*conn)(insert_into(table).set(details::make_assignments<Reflect, Model, Table>(std::forward<Model>(_model), std::forward<Table>(table))));
//         }, std::forward<Model>(model));
//     }
//
// };
