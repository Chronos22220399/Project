#include <Cases/get_pooled_conn_ptr_case.hpp>
#include <Model/AdminModel.h>
#include <Model/GeneralModel.hpp>
#include <Utils/Jwt.h>
#include <crow.h>
#include <future>
#include <nlohmann/json.hpp>
#include <random>
#include <sstream>

int main() {
    using namespace std;
    Utils::test("1", []() {
        using json = nlohmann::json;
        Utils::Jwt::Header header{.alg = "HS256", .typ = "JWT"};
        Utils::Jwt::Payload payload{"hello", "name", 30000};

        auto result = Utils::Jwt::instance().serialize(header, payload);
        fmt::println("jwt: {}", result.jwt);
        auto check_result = Utils::Jwt::instance().check_jwt(result);
        fmt::println("check result is: {}",
                     check_result == Utils::Jwt::JwtCheckResult::isValid);
        fmt::println("check result is: {}",
                     check_result == Utils::Jwt::JwtCheckResult::notMatched);
        fmt::println("check result is: {}",
                     check_result == Utils::Jwt::JwtCheckResult::expired);
    });

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
