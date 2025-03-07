#include <Model/AdminModel.h>
#include <Model/GeneralModel.hpp>
#include <Utils/Encrypter.h>
#include <crow.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/encoder.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
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

std::string hmac_sha256(const std::string &key, const std::string &data) {
    unsigned char *result;
    unsigned int len = SHA256_DIGEST_LENGTH;
    result = HMAC(EVP_sha256(), key.c_str(), key.length(),
                  (unsigned char *)data.c_str(), data.length(), NULL, NULL);
    return std::string(reinterpret_cast<char *>(result), len);
}

std::string base64_encode(const std::string &in) {
    BIO *bio, *b64;
    char *encoded;
    size_t length = in.length();

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, in.c_str(), length);
    BIO_flush(bio);
    BIO_get_mem_data(bio, &encoded);
    std::string result(encoded, length);

    BIO_free_all(bio);
    return result;
}

std::string base64url_encode(const std::string &in) {
    std::string base64 = base64_encode(in);

    std::string base64url = base64;
    std::replace(base64url.begin(), base64url.end(), '+', '-');
    std::replace(base64url.begin(), base64url.end(), '/', '_');

    base64url.erase(std::remove(base64url.begin(), base64url.end(), '='),
                    base64url.end());
    return base64url;
}

std::string base64url_decode(const std::string &in) {
    std::string base64 = in;

    std::replace(base64.begin(), base64.end(), '-', '+');
    std::replace(base64.begin(), base64.end(), '_', '/');

    while (base64.length() % 4 != 0) {
        base64.push_back('=');
    }

    BIO *bio, *b64;
    char *decoded;
    size_t length = base64.length();

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, base64.c_str(), length);
    BIO_flush(bio);
    BIO_get_mem_data(bio, &decoded);
    std::string result(decoded, length);

    BIO_free_all(bio);
    return result;
    return {};
}

int main() {
    using namespace std;

    std::string header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
    std::string payload =
        "{\"sub\":\"1234567890\",\"name\":\"John Doe\",\"iat\":1516239022}";

    std::string header_base64url = base64url_encode(header);
    std::string payload_base64url = base64url_encode(payload);

    std::cout << "Header (Base64Url): " << header_base64url << std::endl;
    std::cout << "Payload (Base64Url): " << payload_base64url << std::endl;

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
