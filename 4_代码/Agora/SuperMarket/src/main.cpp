#include <Model/GeneralModel.hpp>
#include <crow.h>
#include <Model/AdminModel.h>



int main() {
    using namespace std;
    static_assert(std::is_same_v<utils::make_even_index_sequence<3>, std::index_sequence<1, 3>>);

    Model::AdminModel model;
    auto admin = model.get_admin_by_id(74);
    cout << admin.id << " " << admin.username << "\n";

    crow::SimpleApp app{};
    CROW_ROUTE(app, "/get_all_admins")([]() {
        Model::AdminModel model{};
        auto admins = model.get_all_admins();
        std::string ret = "";
        for (const auto &admin : admins) {
            ret += admin.username + "\r\n";
        }
        return ret;
    });


    app.port(18080).multithreaded().run();

    return 0;
}
