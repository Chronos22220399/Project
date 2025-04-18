#include "../include/Utils/Jwt/Jwt.h"
#include "../include/Utils/Base64.h"
#include "../include/Utils/Encrypter.h"
#include "../include/Utils/Jwt/JwtValidationStrategy.hpp"
#include "../include/Utils/RandomGenerator.h"
#include "../include/Utils/Utils.hpp"
#include <chrono>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#define DEBUG_MODE

using namespace Utils;
using namespace nlohmann;

class Jwt::JwtImpl {
  public:
    JwtImpl() : validater(std::make_unique<HS256ValidationStrategy>()) {}

    ~JwtImpl() = default;

    SerializeResult serialize(const Header &header, const Payload &payload) {
        auto headerStr = header.to_json().dump(4);
        auto payloadStr = payload.to_json().dump(4);

        auto headerB64 = base64_.url_encode(headerStr);
        auto payloadB64 = base64_.url_encode(payloadStr);

        auto data = headerB64 + "." + payloadB64;
        auto secretKey = generator_.generate_string(32);
        // TODO: 将 hmac_sha256 更改为哈希策略
        auto signature = encrypter_.hmac_sha256(secretKey, data);
        auto signatureB64 = base64_.url_encode(signature);

        auto jwt = headerB64 + "." + payloadB64 + "." + signatureB64;

        return {secretKey, jwt};
    }

    Jwt::ValidationResult validate(const std::string &jwt,
                                   const std::string &secretKey) {
        JwtDecodeResult decoded = JwtDecoder::decode(jwt, base64_);
        auto result = validater->validate_signature(decoded, secretKey);
        if (result == Jwt::ValidationResult::NotMatched) {
            return result;
        }
        result = validater->validate_claims(decoded);
        return result;
    }

  private:
    Utils::RandomGenerator generator_;
    Utils::Encrypter encrypter_;
    Utils::Base64 base64_;
    std::unique_ptr<JwtValidationStrategy> validater;
};

Jwt::SerializeResult Jwt::serialize(const Header &header,
                                    const Payload &payload) {
    return impl->serialize(header, payload);
}

Jwt::ValidationResult Jwt::validate(const std::string &jwtStr,
                                    const std::string &secretKey) {
    return impl->validate(jwtStr, secretKey);
}

Jwt::Jwt() : impl(std::make_unique<JwtImpl>()) {}

Jwt &Jwt::instance() {
    static Jwt instance;
    return instance;
};

Jwt::~Jwt() = default;
