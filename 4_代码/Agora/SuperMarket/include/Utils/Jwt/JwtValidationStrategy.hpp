//
// Created by 无铭 on 25-3-12.
//

#ifndef JWTVALIDATIONSTRATEGY_HPP
#define JWTVALIDATIONSTRATEGY_HPP
#include <string>


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
#endif //JWTVALIDATIONSTRATEGY_HPP
