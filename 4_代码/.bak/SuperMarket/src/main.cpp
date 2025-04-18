#include <../include/Utils/Jwt/Jwt.h>
// #include <Cases/get_pooled_conn_ptr_case.hpp>
<<<<<<< HEAD
#include "../../cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest-param-test.h"

#include <Model/AdminModel.h>
=======
#include <Model/UserModel.h>
    >>>>>>> 4c5689a0f1af2e87abcfc520adb4dceccdfe1a57
#include <Model/GeneralModel.hpp>
#include <Utils/Log.hpp>
#include <Utils/RBAC/BasicUser.hpp>
#include <Utils/RBAC/PermissionManager.h>
#include <crow.h>
#include <fstream>
#include <future>
#include <nlohmann/json.hpp>
#include <queue>
#include <random>
#include <sqlpp11/sqlpp11.h>
#include <sstream>

    struct TmpUser : public Utils::BasicUser {
    std::string role = "user";
};

// struct CustumRegDB final : public Utils::RegDBStrategy {
//   public:
//     CustumRegDB() {}
//     ~CustumRegDB() {}
//
//     bool save(std::shared_ptr<Utils::BasicUser> user) override { return
//     false; }
//
//     bool query_name(const std::string &name) override {
//         return model.get_admin_by_username(name).has_value();
//     }
//
//     Model::AdminModel model;
// };

int main() {
    using namespace std;
    // Utils::test("Register", []()
    // {
    //     std::unique_ptr<Utils::BasicUser> user = std::make_unique<TmpUser>();
    // });

    Utils::test("permission management", []() {
        Utils::PermissionManager manager;
        std::unique_ptr<Utils::BasicUser> user = std::make_unique<TmpUser>();
        auto res = manager.check_access(*user, Utils::Resource::Goods,
                                        Utils::Action::Read);
        fmt::println("{}", res);
        res = manager.check_access(*user, Utils::Resource::Goods,
                                   Utils::Action::Write);
        fmt::println("{}", res);
        res = manager.check_access(*user, Utils::Resource::Goods,
                                   Utils::Action::Delete);
        fmt::println("{}", res);
    });

    // Utils::test("generate numbers", []()
    // {
    //     Utils::RandomGenerator g;
    //     auto res = g.generate_numbers_from(0, 30, 10);
    //     for (auto &i : res)
    //     {
    //         Utils::test("generate numbers", []()
    //         {
    //             Utils::RandomGenerator g;
    //             auto res = g.generate_numbers_from(0, 30, 10);
    //             for (auto &i: res)
    //             {
    //                 LOG("{}", i);
    //             }
    //         });
    //     }
    // });

    // Utils::test("generate number", []()
    // {
    //     Utils::RandomGenerator g;
    //     auto res = g.generate_number_from(-30, 30);
    //     LOG("{}", res);
    // });
    //
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

    // auto admin = model.get_admin_by_id(74);
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

    // CROW_ROUTE(app, "/create_admin/<string>/<string>")(
    //     [](std::string username, std::string password) {
    //         Model::AdminModel model;
    //         Model::AdminModel::Admin_ admin;
    //         admin.username = username;
    //         admin.password = password;
    //         admin.role = "admin";
    //         if (model.create_admin(admin)) {
    //             return "Successfully created admin";
    //         }
    //         return "Failed to create admin";
    //     });
    //
    // CROW_ROUTE(app, "/get_admin_by_id/<int>")([](int id) {
    //     Model::AdminModel model{};
    //     std::stringstream ss;
    //     auto admins = model.get_admin_by_id(id);
    //     if (!admins.has_value()) {
    //         return "admin not found";
    //     }
    //     auto admin = admins.value();
    //     ss << admin.id << " " << admin.username << " " << admin.password;
    //     return std::move(ss.str().c_str());
    // });
<<<<<<< HEAD
    //
=======

>>>>>>> 4c5689a0f1af2e87abcfc520adb4dceccdfe1a57
    // app.port(18080).multithreaded().run();

    return 0;
}
