#include <Utils/Base64.h>
#include <Utils/Jwt.h>
#include <Utils/RandomGenerator.h>
#include <Utils/Utils.hpp>
#include <chrono>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#define DEBUG_MODE

using namespace Utils;
using namespace nlohmann;

struct JwtDecodeResult {
    const std::string header_b64;
    const std::string payload_b64;
    const std::string signature_b64;
    const json header_json;
    const json payload_json;

    JwtDecodeResult(const std::string &header_b64,
                    const std::string &payload_b64,
                    const std::string &signature_b64, const json &header_json,
                    const json &payload_json)
        : header_b64(header_b64), payload_b64(payload_b64),
          signature_b64(signature_b64), header_json(header_json),
          payload_json(payload_json) {}
};

class JwtDecoder {
  public:
    static JwtDecodeResult decode(const std::string &jwtStr,
                                  const Base64 &base64) {
        auto pos1 = jwtStr.find(".");
        auto pos2 = jwtStr.find(".", pos1 + 1);

        auto header_b64 = jwtStr.substr(0, pos1);
        auto payload_b64 = jwtStr.substr(pos1 + 1, pos2 - pos1 - 1);
        auto signature_b64 = jwtStr.substr(pos2 + 1);

        LOG(header_b64);
        LOG(payload_b64);
        LOG(signature_b64);

        return JwtDecodeResult(header_b64, payload_b64, signature_b64,
                               json::parse(base64url_decode(header_b64)),
                               json::parse(base64url_decode(payload_b64)));
    }

  private:
    static std::string base64url_decode(const std::string &input) {
        Base64 base64;
        return base64.url_decode(input);
    }
};

class JwtValidationStrategy {
  public:
    virtual ~JwtValidationStrategy() = default;

    // 验证签名策略
    virtual Jwt::ValidationResult
    validate_signature(const JwtDecodeResult &decoded,
                       const std::string &secret_key) const = 0;

    // 验证业务逻辑策略
    virtual Jwt::ValidationResult
    validate_claims(const JwtDecodeResult &decoded) const = 0;
};

class HS256ValidationStrategy : public JwtValidationStrategy {
    // 验证签名策略
    Jwt::ValidationResult
    validate_signature(const JwtDecodeResult &decoded,
                       const std::string &secret_key) const override {
        const auto data = decoded.header_b64 + "." + decoded.payload_b64;
        const auto expected_sig = hmac_sha256(secret_key, data);
        if (base64url_encode(expected_sig) != decoded.signature_b64) {
            return Jwt::ValidationResult::NotMatched;
        }
        return Jwt::ValidationResult::Valid;
    }

    // 验证业务逻辑策略
    Jwt::ValidationResult
    validate_claims(const JwtDecodeResult &decoded) const override {
        auto now = std::chrono::system_clock::now();
        auto timeStamp = std::chrono::duration_cast<std::chrono::seconds>(
                             now.time_since_epoch())
                             .count();
        const uint64_t iat = decoded.payload_json["iat"];
        const uint64_t exp = decoded.payload_json["exp"];

        if (timeStamp > iat + exp) {
            return Jwt::ValidationResult::Expired;
        }
        return Jwt::ValidationResult::Valid;
    }

  private:
    static std::string hmac_sha256(const std::string &secret_key,
                                   const std::string &data) {
        const auto expected_sig = Encrypter::hmac_sha256(secret_key, data);
        return expected_sig;
    }

    static std::string base64url_encode(const std::string &input) {
        Base64 base64;
        return base64.url_encode(input);
    }
};

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
