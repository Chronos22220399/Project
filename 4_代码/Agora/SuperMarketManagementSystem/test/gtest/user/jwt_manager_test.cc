#include <chrono>
#include <common/user/jwt_manager.hpp>
#include <gtest/gtest.h>
#include <thread>

class JwtManagerTest : public ::testing::Test {
  protected:
  void SetUp() override
  {
    JwtManager::getInstance().init("test_secret", 1);  // 默认过期时间1秒
  }
};

TEST_F(JwtManagerTest, GenerateTokenContainsUserId)
{
  std::string token = JwtManager::getInstance().generateToken("user123");
  auto decoded = jwt::decode(token);
  ASSERT_TRUE(decoded.has_payload_claim("uid"));
  EXPECT_EQ(decoded.get_payload_claim("uid").as_string(), "user123");
}

TEST_F(JwtManagerTest, VerifyValidToken)
{
  std::string token = JwtManager::getInstance().generateToken("user123");
  auto result = JwtManager::getInstance().verifyToken(token);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), "user123");
}

TEST_F(JwtManagerTest, ExpiredTokenFails)
{
  JwtManager::getInstance().init("test_secret", 0);  // 立即过期
  std::string token = JwtManager::getInstance().generateToken("user123");
  // 确保Token过期
  std::this_thread::sleep_for(std::chrono::seconds(1));
  auto result = JwtManager::getInstance().verifyToken(token);
  EXPECT_FALSE(result.has_value());
}

TEST_F(JwtManagerTest, InvalidSignature)
{
  JwtManager::getInstance().init("correct_secret", 3600);
  std::string token = JwtManager::getInstance().generateToken("user123");

  // 使用错误密钥验证
  JwtManager::getInstance().init("wrong_secret", 3600);
  auto result = JwtManager::getInstance().verifyToken(token);
  EXPECT_FALSE(result.has_value());
}

TEST_F(JwtManagerTest, TamperedTokenFails)
{
  std::string token = JwtManager::getInstance().generateToken("user123");
  // 简单篡改Token
  token.back() = 'x';
  auto result = JwtManager::getInstance().verifyToken(token);
  EXPECT_FALSE(result.has_value());
}

TEST_F(JwtManagerTest, MissingUidFails)
{
  // 构造无uid的Token
  auto token = jwt::create()
                 .set_issued_at(std::chrono::system_clock::now())
                 .set_expires_at(std::chrono::system_clock::now()
                                 + std::chrono::seconds(3600))
                 .sign(jwt::algorithm::hs256{"test_secret"});

  auto result = JwtManager::getInstance().verifyToken(token);
  EXPECT_FALSE(result.has_value());
}
