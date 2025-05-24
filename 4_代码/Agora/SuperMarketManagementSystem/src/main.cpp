// stl
#include <chrono>
#include <future>
#include <iostream>
#include <vector>
// third_party
#include <crow.h>
// tools
#include <common/config_utils.h>
#include <common/global_id_cache.hpp>
#include <common/user/jwt_manager.hpp>
#include <common/user/vcode_manager.hpp>
// repos
#include <repository/common/unit_repository.h>
#include <repository/goods/goods_category_repository.h>
#include <repository/goods/goods_repository.h>
#include <repository/goods/promotion_repository.h>
#include <repository/warehouse/warehouse_repository.h>
// router
#include <router/init_router.h>
// register
#include <register/include.h>

using namespace std;


void initCache()
{
  common::initCache();
  goods::initCache();
  warehouse::initCache();
}

void initConfig(const ConfigManager& configMgr)
{
  auto config_file = "./SuperMarketManagementSystem/config/config.json";
  // 初始化配置管理模块
  configMgr.init(config_file);
  // 初始化验证码管理模块
  VCodeManager::getInstance().init(configMgr.getVCodeTTL());
  // 初始化 jwt 管理模块
  JwtManager::getInstance().init(configMgr.getSecret(),
                                 configMgr.getTokenExpireMinutes());
  // 启动服务
}


int main()
{
  crow::SimpleApp app;
  auto& configMgr = ConfigManager::getInstance();

  initRouters(app);
  initCache();
  initConfig(configMgr);

  app.multithreaded().port(configMgr.getPort()).run();
  return 0;
}
