#include <Model/GeneralModel.hpp>
#include <crow.h>
#include <include/admin.h>

namespace Model {
struct Admin {
    size_t id;
    std::string username;
    std::string password;
};

struct AdminModel : GenericModel<Admin, Admin_::Admin> {};

// 特化出从模型到表的反射
template <> struct ReflectTable<Admin, Admin_::Admin> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&Admin::id, &Admin_::Admin::id),
        std::make_pair(&Admin::username, &Admin_::Admin::username),
        std::make_pair(&Admin::password, &Admin_::Admin::password));
};

template <typename AdminTableRow> struct ReflectTableRow<Admin, AdminTableRow> {
    static constexpr auto assign_model(AdminTableRow &&row) {
        return Admin{.id = static_cast<size_t>(row.id),
                     .username = row.username,
                     .password = row.password};
    }
};
} // namespace Model

void usage() {
    Model::AdminModel model;
    for (size_t i = 60; i < 70; ++i) {
        Model::Admin admin{.username = std::to_string(i + 30),
                           .password = "password"};
        model.insert(Model::Admin{.username = std::to_string(i),
                                  .password = std::to_string(i)});
        model.update(admin, Admin_::Admin{}.username == std::to_string(i));
    }
    auto rows = model.select(Admin_::Admin{}.id >= 44);
    for (auto &row : rows) {
        std::cout << row.id << " " << row.username << " " << row.password
                  << std::endl;
    }
}

int main() {
    // using namespace std;
    // Model::AdminModel model{};
    // auto admins = model.select(Admin_::Admin{}.id > 0);
    // for (const auto &admin : admins) {
    //     fmt::println("{} {}", admin.username, admin.password);
    // }
    usage();

    // crow::SimpleApp app{};
    // CROW_ROUTE(app, "/get_all_admins")([]() {
    //     Model::AdminModel model{};
    //     auto admins = model.select(Admin_::Admin{}.id >= 0);
    //     std::string ret = "";
    //     for (const auto &admin : admins) {
    //         ret += admin.username + "\r\n";
    //     }
    //     return ret;
    // });
    //
    // CROW_ROUTE(app, "/get_admin_by_id/<int>")([](size_t id) {
    //     Model::AdminModel model{};
    //     auto admins = model.select(Admin_::Admin{}.id == id);
    //     std::string ret = "";
    //     for (const auto &admin : admins) {
    //         ret += admin.username + "\r\n";
    //     }
    //     return ret;
    // });
    //
    // CROW_ROUTE(app,
    //            "/get_admin_by_username/<string>")([](std::string username) {
    //     Model::AdminModel model{};
    //     auto admins = model.select(Admin_::Admin{}.username == username);
    //     std::string ret = "";
    //     for (const auto &admin : admins) {
    //         fmt::println("{} {}", admin.username, admin.password);
    //         ret += admin.username + "\r\n";
    //     }
    //     return ret;
    // });
    //
    // app.port(18080).multithreaded().run();

    return 0;
}
