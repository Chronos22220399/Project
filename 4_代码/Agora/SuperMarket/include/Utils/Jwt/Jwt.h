#pragma once
#include "../Encrypter.h"
#include "../RandomGenerator.h"
#include "../Utils.hpp"
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

        Header() : alg("HS256"), typ("JWT") {}

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
        std::string role;

        Payload() = default;

        Payload(std::string sub, std::string name, size_t exp = 3000,
                const std::string &role = "customer")
            : sub(sub), name(name), exp(exp), role(role) {
            auto now = std::chrono::system_clock::now();
            auto timeStamp = std::chrono::duration_cast<std::chrono::seconds>(
                                 now.time_since_epoch())
                                 .count();
            iat = timeStamp;
        }

        json to_json() const {
            auto j = json{{"sub", sub},
                          {"name", name},
                          {"iat", iat},
                          {"exp", exp},
                          {"role", role}};
            return j;
        }

        static Payload from_json(const json &j) {
            Payload payload;
            j.at("sub").get_to(payload.sub);
            j.at("name").get_to(payload.name);
            j.at("iat").get_to(payload.iat);
            j.at("exp").get_to(payload.exp);
            j.at("role").get_to(payload.role);
            return payload;
        }
    };

    struct SerializeResult {
        std::string secretKey;
        std::string jwt;
    };

    enum class ValidationResult { Valid, Expired, NotMatched };

    SerializeResult serialize(const Header &header, const Payload &payload);

    ValidationResult validate(const std::string &jwtStr,
                              const std::string &secretKey);

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
