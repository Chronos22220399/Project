#include <chrono>
#include <common/user/vcode_manager.hpp>
#include <gtest/gtest.h>
#include <thread>

class VCodeManagerTest : public ::testing::Test {
  protected:
  void SetUp() override
  {
    VCodeManager::getInstance().init(1);  // 默认设置1秒TTL便于测试
  }
};

TEST_F(VCodeManagerTest, GenerateValidCode)
{
  auto& manager = VCodeManager::getInstance();
  const std::string phone = "13800138000";

  // 生成验证码
  std::string code = manager.generateCode(phone);

  // 验证格式
  EXPECT_EQ(code.length(), 6);
  EXPECT_TRUE(std::all_of(code.begin(), code.end(), ::isdigit));
}

TEST_F(VCodeManagerTest, VerifyCorrectCode)
{
  auto& manager = VCodeManager::getInstance();
  const std::string phone = "13800138000";
  const std::string code = manager.generateCode(phone);

  auto result = manager.verifyCode(phone, code);

  EXPECT_TRUE(result.success);
  EXPECT_TRUE(result.error.empty());
}

TEST_F(VCodeManagerTest, ExpiredCode)
{
  auto& manager = VCodeManager::getInstance();
  const std::string phone = "13800138000";
  manager.generateCode(phone);

  // 等待过期
  std::this_thread::sleep_for(std::chrono::seconds(2));

  auto result = manager.verifyCode(phone, "000000");
  EXPECT_FALSE(result.success);
  EXPECT_EQ(result.error, "Code expired.");
}

TEST_F(VCodeManagerTest, WrongCode)
{
  auto& manager = VCodeManager::getInstance();
  const std::string phone = "13800138000";
  manager.generateCode(phone);

  auto result = manager.verifyCode(phone, "123456");

  EXPECT_FALSE(result.success);
  EXPECT_EQ(result.error, "Code is not matched.");
}

TEST_F(VCodeManagerTest, CodeRegeneration)
{
  auto& manager = VCodeManager::getInstance();
  const std::string phone = "13800138000";

  // 第一次生成
  std::string code1 = manager.generateCode(phone);
  // 立即重新生成
  std::string code2 = manager.generateCode(phone);

  // 验证旧码失效
  auto result1 = manager.verifyCode(phone, code1);
  EXPECT_FALSE(result1.success);

  // 验证新码有效
  auto result2 = manager.verifyCode(phone, code2);
  EXPECT_FALSE(result2.success);
}

TEST_F(VCodeManagerTest, NonExistentPhone)
{
  auto& manager = VCodeManager::getInstance();

  auto result = manager.verifyCode("non_exist_phone", "123456");

  EXPECT_FALSE(result.success);
  EXPECT_EQ(result.error, "Can't find code");
}
