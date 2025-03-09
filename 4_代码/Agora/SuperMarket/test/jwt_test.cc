#include <Utils/Jwt.h>
#include <gtest/gtest.h>

TEST(jwt_test, test_check) {
    using namespace Utils;
    Jwt::Header header;
    Jwt::Payload payload{"test", "Ess", 3000};

    auto result = Jwt::instance().serialize(header, payload);
    auto jwtStr = result.jwt;
    auto secretKey = result.secretKey;
    auto res = Jwt::instance().validate(jwtStr, secretKey);
    EXPECT_EQ(res, Jwt::ValidationResult::Valid);
    EXPECT_NE(res, Jwt::ValidationResult::NotMatched);
    EXPECT_NE(res, Jwt::ValidationResult::Expired);

    jwtStr += "1";
    res = Jwt::instance().validate(jwtStr, secretKey);
    EXPECT_NE(res, Jwt::ValidationResult::Valid);
    EXPECT_EQ(res, Jwt::ValidationResult::NotMatched);
    EXPECT_NE(res, Jwt::ValidationResult::Expired);

    // payload.name = "cal";
    // auto ke7 = result.secretKey;
}

TEST(jwt_test, test_expire) {
    using namespace Utils;
    Jwt::Header header;
    Jwt::Payload payload{"test", "Ess", 0};

    auto result = Jwt::instance().serialize(header, payload);
    auto jwtStr = result.jwt;
    auto secretKey = result.secretKey;
    auto res = Jwt::instance().validate(jwtStr, secretKey);
    EXPECT_EQ(res, Jwt::ValidationResult::Valid);
    EXPECT_NE(res, Jwt::ValidationResult::NotMatched);
    EXPECT_NE(res, Jwt::ValidationResult::Expired);
}
