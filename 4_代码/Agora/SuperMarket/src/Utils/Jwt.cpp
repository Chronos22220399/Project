#include <Utils/Jwt.h>
#include <Utils/RandomGenerator.h>
#include <Utils/Utils.hpp>
#include <chrono>
#include <nlohmann/json.hpp>
#include <string>

using namespace Utils;

class Jwt::JwtImpl {
  public:
    JwtImpl() = default;

    ~JwtImpl() = default;

    SerializeResult serialize(const Header &header, const Payload &payload) {
        auto headerStr = header.to_json().dump(4);
        auto payloadStr = payload.to_json().dump(4);

        auto headerB64 = base64_.url_encode(headerStr);
        auto payloadB64 = base64_.url_encode(payloadStr);

        auto data = headerB64 + "." + payloadB64;
        auto secretKey = generator_.generate_string(32);
        auto signature = encrypter_.hmac_sha256(secretKey, data);
        auto signatureB64 = base64_.url_encode(signature);

        auto jwt = headerB64 + "." + payloadB64 + "." + signatureB64;

        return {secretKey, jwt};
    }

    JwtCheckResult check_jwt(const SerializeResult &result) {
        using json = nlohmann::json;
        auto secretKey = result.secretKey;
        auto jwt = result.jwt;

        auto pos1 = jwt.find(".");
        auto pos2 = jwt.find(".", pos1 + 1);

        auto headerB64 = jwt.substr(0, pos1);
        auto payloadB64 = jwt.substr(pos1 + 1, pos2 - pos1 - 1);
        auto signatureB64 = jwt.substr(pos2 + 1);

        LOG(headerB64);
        LOG(payloadB64);
        LOG(signatureB64);

        auto encryptedData =
            encrypter_.hmac_sha256(secretKey, headerB64 + "." + payloadB64);
        // jwt 被篡改
        if (base64_.url_encode(encryptedData) != signatureB64) {
            return JwtCheckResult::notMatched;
        }
        // jwt 失效
        auto payloadStr = base64_.url_decode(payloadB64);
        json j = json::parse(payloadStr);
        Payload payload = Payload::from_json(j);

        auto now = std::chrono::system_clock::now();
        auto timeStamp = std::chrono::duration_cast<std::chrono::seconds>(
                             now.time_since_epoch())
                             .count();

        if (payload.iat + payload.exp < timeStamp) {
            return JwtCheckResult::expired;
        }
        return JwtCheckResult::isValid;
    }

    Utils::RandomGenerator generator_;
    Utils::Encrypter encrypter_;
    Utils::Base64 base64_;
};

Jwt::SerializeResult Jwt::serialize(const Header &header,
                                    const Payload &payload) {
    return impl->serialize(header, payload);
}

Jwt::JwtCheckResult Jwt::check_jwt(const SerializeResult &result) {
    return impl->check_jwt(result);
}

Jwt::Jwt() : impl(std::make_unique<JwtImpl>()) {}

Jwt &Jwt::instance() {
    static Jwt instance;
    return instance;
};

Jwt::~Jwt() = default;
