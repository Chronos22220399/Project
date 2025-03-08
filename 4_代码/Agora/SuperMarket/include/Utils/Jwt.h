#pragma once
#include <Utils/Base64.h>
#include <Utils/Encrypter.h>
#include <Utils/RandomGenerator.h>
#include <Utils/Utils.hpp>
#include <chrono>
#include <nlohmann/json.hpp>
#include <string>

namespace Utils {

class Jwt {
  public:
    struct Header {
        using json = nlohmann::json;
        std::string alg;
        std::string typ;

        json to_json() const {
            auto j = json{{"alg", this->alg}, {"typ", this->typ}};
            return j;
        }

        static Header from_json(const json &j) {
            Header header;
            j.at("alg").get_to(header.alg);
            j.at("typ").get_to(header.typ);
            return header;
        }
    };

    struct Payload {
        using json = nlohmann::json;
        std::string sub;
        std::string name;
        size_t iat;
        size_t exp;

        Payload() = default;

        Payload(std::string sub, std::string name, size_t exp = 3000)
            : sub(sub), name(name), exp(exp) {
            auto now = std::chrono::system_clock::now();
            auto timeStamp = std::chrono::duration_cast<std::chrono::seconds>(
                                 now.time_since_epoch())
                                 .count();
            iat = timeStamp;
        }

        json to_json() const {
            auto j =
                json{{"sub", sub}, {"name", name}, {"iat", iat}, {"exp", exp}};
            return j;
        }

        static Payload from_json(const json &j) {
            Payload payload;
            j.at("sub").get_to(payload.sub);
            j.at("name").get_to(payload.name);
            j.at("iat").get_to(payload.iat);
            j.at("exp").get_to(payload.exp);
            return payload;
        }
    };

    struct SerializeResult {
        std::string secretKey;
        std::string jwt;
    };

    enum class JwtCheckResult { isValid, notMatched, expired };

    SerializeResult serialize(const Header &header, const Payload &payload);

    JwtCheckResult check_jwt(const SerializeResult &result);

    Jwt(Jwt &&) = delete;

    ~Jwt();

  private:
    Jwt();
    class JwtImpl;

  public:
    static Jwt &instance();

  private:
    std::unique_ptr<JwtImpl> impl;
};

} // namespace Utils
