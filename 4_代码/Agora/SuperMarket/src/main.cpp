#include <Cases/get_pooled_conn_ptr_case.hpp>
#include <Model/AdminModel.h>
#include <Model/GeneralModel.hpp>
#include <Utils/Jwt.h>
#include <Utils/Log.hpp>
#include <Utils/RBAC/PermissionManager.h>
#include <crow.h>
#include <fstream>
#include <future>
#include <nlohmann/json.hpp>
#include <random>
#include <sqlpp11/sqlpp11.h>
#include <sstream>

struct User : public Utils::BasicUser {};

int main() {
    using namespace std;
    Utils::test("permission management", []() {
        Utils::PermissionManager manager;
        std::unique_ptr<Utils::BasicUser> user = std::make_unique<User>();
        auto res = manager.check_access(user, Utils::Resource::Goods,
                                        Utils::Action::Read);
        fmt::println("{}", res);
        res = manager.check_access(user, Utils::Resource::Goods,
                                   Utils::Action::Write);
        fmt::println("{}", res);
        res = manager.check_access(user, Utils::Resource::Goods,
                                   Utils::Action::Delete);
        fmt::println("{}", res);
    });

    Utils::test("generate numbers", []() {
        Utils::RandomGenerator g;
        auto res = g.generate_numbers_from(0, 30, 10);
        for (auto &i : res) {
            LOG("{}", i);
        }
    });

    Utils::test("generate number", []() {
        Utils::RandomGenerator g;
        auto res = g.generate_number_from(-30, 30);
        LOG("{}", res);
    });

    // Utils::test("1", []() {
    //     using json = nlohmann::json;
    //     Utils::Jwt::Header header{};
    //     Utils::Jwt::Payload payload{"hello", "name"};
    //
    //     auto result = Utils::Jwt::instance().serialize(header, payload);
    //     auto jwtStr = result.jwt;
    //     auto secretKey = result.secretKey;
    //     auto check_result = Utils::Jwt::instance().validate(jwtStr,
    //     secretKey);
    //
    //     fmt::println("check result is: {}",
    //                  check_result == Utils::Jwt::ValidationResult::Valid);
    //     fmt::println("check result is: {}",
    //                  check_result ==
    //                  Utils::Jwt::ValidationResult::NotMatched);
    //     fmt::println("check result is: {}",
    //                  check_result == Utils::Jwt::ValidationResult::Expired);
    // });

    // Utils::test("1", []() {
    //     auto mess = "hello, world";
    //     auto res = hmac_sha256("123", mess);
    //     Utils::Base64 base64;
    //     LOG(mess);
    //     LOG(base64.url_encode(res));
    // });

    // Utils::Encrypter::init();
    // crow::SimpleApp app{};
    //
    // Model::AdminModel model;
    // auto admin = model.get_admin_by_id(74);
    // std::stringstream ss;
    // auto psd = Utils::Encrypter::hash_password(admin.password);
    // if (psd) {
    //     ss << "Id: " << admin.id << "\tUsername: " << admin.username
    //        << " \tPassword: " << admin.password
    //        << "\tEncrypted Passwrod: " << psd.value() << "\n";
    // }
    // std::cout << ss.str() << "\n";
    // std::cout << "password is match: "
    //           << Utils::Encrypter::verify_password(psd.value(),
    //           admin.password)
    //           << "\n";

    // CROW_ROUTE(app, "/get_all_admins")([]() {
    //     Model::AdminModel model{};
    //     auto admins = model.get_all_admins();
    //     return static_cast<std::string>(ss.str());
    // });

    // app.port(18080).multithreaded().run();

    return 0;
}
