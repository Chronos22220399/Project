## 📁 项目目录结构
```makefile
supermarket-management-system/
├── CMakeLists.txt
├── README.md
├── config/
│   └── config.json            # 配置文件，如端口号、数据库信息等
├── include/                   # 公共头文件
│   ├── common/                # 公共定义、工具类、通用宏等
│   ├── controller/            # 控制器层，处理路由逻辑
│   ├── service/               # 服务层，封装业务逻辑
│   ├── repository/            # 数据访问层，操作 sqlpp/sqlite
│   ├── model/                 # 数据模型，定义表结构/DTO/VO
│   └── router/                # 路由注册
├── src/
│   ├── main.cpp               # 程序入口
│   ├── common/
│   ├── controller/
│   ├── service/
│   ├── repository/
│   ├── model/
│   └── router/
├── modules/                  # 每个业务模块单独目录，存放边界逻辑（如模块对应的数据校验、各类模块相关工具）
│   ├── goods/                # 商品管理模块
│   │   ├── include/
│   │   └── src/
│   ├── warehouse/            # 仓库管理模块
│   │   ├── include/
│   │   └── src/
│   └── finance/              # 财务管理模块
│       ├── include/
│       └── src/
├── third_party/              # 三方库（若自带/封装用）
├── test/                     # 单元测试
│   └── ...
└── scripts/                  # 构建、部署、初始化脚本
    └── init_db.sql
```
> 当前将核心逻辑放在根目录下的 include/ 和 src/ 下统一管理，模块内封装便捷逻辑作为插件使用，后续模块变得庞大后可以逐步将整个模块（controller + service + repo）迁移如 modules/ 下
