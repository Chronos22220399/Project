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

### 说明

#### dto 定义说明

对于表自身的外部id和内部id, 仅会暴露外部id,内部id用于保证唯一性以及快速查找,
对于表中的外键，统一用后缀 rk_id 标识，在序列化和反序列化时会通过全局缓存查找对应的
id 后存储（内部id对应外部id）

##### 序列化时

序列化时会将json中的外部id（外键的，自身的主键id不做处理）给映射为内部id作为dto的参数

##### 反序列化时

反序列化时会将dto中的内部id（外键的，自身的主键id不做处理）给映射为外部id作为json的参数

#### 全局缓存的规则

全局缓存内部同时维护两对映射：

1. 内部id -> 外部id
2. 外部id -> 内部id

###### 查找

全局缓存首先在缓存内部查找，若找不到则会在通过表名对应的查找函数在数据库中查找并存储，缓存最大能容纳
一万条记录，超过的记录会被删除

##### 更新

全局缓存的更新接收表名和内部id、外部id,每次更新会同时更新两对映射以保持一致性

##### 删除

通过 invalidate 删除缓存中的映射

### 项目文件创建

#### 通过code_gen脚本创建脚手架

`python ./scripts/single_code_gen.py <指定的ddl的路径>`

报告：
实现：整体设计（整体架构、详细到每一层 --> 局部设计，我把我写的讲一下，

// 我负责 商品管理模块、用户、会员、
