//
// Created by 无铭 on 25-3-12.
//

#ifndef JWTDECODER_HPP
#define JWTDECODER_HPP
#include <nlohmann/json.hpp>
#include <string>
#include "../Base64.h"

namespace Utils {

using nlohmann::json;

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
}

#endif //JWTDECODER_HPP
