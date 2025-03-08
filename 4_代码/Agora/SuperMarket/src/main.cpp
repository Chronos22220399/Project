#include <Cases/get_pooled_conn_ptr_case.hpp>
#include <Model/AdminModel.h>
#include <Model/GeneralModel.hpp>
#include <Utils/Base64.h>
#include <Utils/Encrypter.h>
#include <crow.h>
#include <future>
#include <sstream>

struct Header {
    std::string alg;
    std::string typ;
};

struct Payload {
    std::string sub;
    std::string name;
    std::string iat;
    std::string exp;
};

struct Jwt {};

template <typename Operation, typename... Args>
void test(const std::string &caseName, Operation &&operation, Args &&...args) {
    fmt::println("\n -------- Test Case: {} Start -------\n", caseName);
    std::invoke(std::forward<Operation>(operation),
                std::forward<Args>(args)...);
    fmt::println("\n -------- Test Case: {} End -------\n", caseName);
}

int main() {
    using namespace std;

    test("1", []() {
        std::string header = R"({"alg":"HS256","typ":"JWT"})";
        std::string payload =
            R"({"sub":"1234567890","name":"John Doe","iat":1516239022})";

        vector<std::future<void>> futures;
        for (size_t i = 0; i < 10; ++i) {
            futures.emplace_back(async(std::launch::async, [&header,
                                                            &payload]() {
                Utils::Base64 base64;
                std::string header_b64 = base64.url_encode(header);
                std::string payload_b64 = base64.url_encode(payload);

                std::cout << "Header (Base64Url): " << header_b64 << std::endl;
                std::cout << "Payload (Base64Url): " << payload_b64
                          << std::endl;

                std::string decoded_header = base64.url_decode(header_b64);
                std::string decoded_payload = base64.url_decode(payload_b64);

                std::cout << "Decoded Header: " << decoded_header << std::endl;
                std::cout << "Decoded Payload: " << decoded_payload
                          << std::endl;
            }));
        }
        for (auto &f : futures) {
            f.wait();
        }
    });

    test("2", []() {
        Model::AdminModel model;
        model.get_admin_by_id(70);
    });
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
