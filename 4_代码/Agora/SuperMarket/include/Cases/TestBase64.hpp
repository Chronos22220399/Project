#include <../Utils/Jwt/Base64.h>
#include <Utils/Utils.hpp>
#include <future>
#include <iostream>
#include <vector>

inline void test_base64() {
    using namespace std;
    Utils::test("1", []() {
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
}
