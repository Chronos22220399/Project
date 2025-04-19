## 配置详述
通过 `./init.sh` 构建容器,容器创建后会自动调用 setup.sh 对环境进行基础配置

### 错误处理 

#### 权限错误
`./init.sh` 没有权限导致的，使用 `sudo chmod +x init.sh` 配置即可

#### 镜像拉取错误
在使用`./init.sh` 构建容器时若无法获取镜像，则优先检查代理设置（或镜像源设置，二选一即可）

##### 通过 docker-desktop 使用的 docker
请在 ~/.docker/daemon.json 中配置代理或镜像源，以我的配置举例
```json
{
  "builder": {
    "gc": {
      "defaultKeepStorage": "20GB",
      "enabled": true
    }
  },
  "experimental": false,
  "ipv6": false,
  "proxies": {
    "default": {
      "httpProxy": "http://localhost:7897",
      "httpsProxy": "https://localhost:7897",
      "noProxy": "localhost,127.0.0.1,.docker.internal"
    }
  }
}
```
> 其中 ipv6 禁止掉
> httpProxy 和 httpsProxy 请改写成自己的代理地址和端口

##### 非 docker-desktop 启动
创建目录 /etc/systemd/system/docker.service.d/，接着在前述目录下创建并编辑 http-proxy.conf 文件
```bash
sudo mkdir -p /etc/systemd/system/docker.service.d/
sudo vim /etc/systemd/system/docker.service.d/http-proxy.conf
```
在上述文件中添加代理配置
> 以我的配置举例
```bash
[Service]
Environment="HTTP_PROXY=http://proxy-server:port"
Environment="HTTPS_PROXY=http://proxy-server:port"
Environment="NO_PROXY=localhost,127.0.0.1,.docker.internal"
```
接着重启服务
```bash
sudo systemctl daemon-reload
sudo systemctl restart docker
```


## 目录内容介绍

1. cmake/ 存放 cmake 配置文件
2. first/ 当前的测试子项目
3. scripts/ 项目的脚本目录，其内存放cmake第三方库配置脚本、根据 ddl 生成数据库、orm 类头文件的脚本、项目初始化脚本等
4. CMakeLists.txt 根目录的 cmake 管理项，内部存放子项目的公共配置项
5. libraries.json 使用的第三方库的配置文件
6. run.sh 项目编译脚本(限制于 unix 类系统)
7. SuperMarket/ 当前的项目后端

---

## 项目模块
### 超市管理系统模块概述

- #### 商品管理模块
    1. 商品信息录入
    2. 商品分类管理
    3. 商品库存管理
    4. 商品价格管理
    5. 促销活动管理

- #### 会员管理模块
    1. 会员信息录入
    2. 会员等级查询
    3. 积分政策管理
    4. 会员消费记录管理
    5. 会员积分兑换管理

- #### 员工信息管理
    1. 员工信息录入
    2. 岗位管理
    3. 员工排班管理
    4. 考勤管理
    5. 工资管理

- #### 销售管理模块
    1. 销售订单录入
    2. 销售退货管理
    3. 销售统计报表
    4. 商品销售排行榜

- #### 供应商管理模块
    1. 供应商信息录入
    2. 供应商合同管理
    3. 供应商评价管理
    4. 采购订单管理

- #### 仓库管理模块
    1. 仓库信息管理
    2. 商品入库管理
    3. 商品出库管理
    4. 库存盘点管理
    5. 库存报警管理

- #### 财务管理模块
    1. 收银管理
    2. 业务报表生成
    3. 成本核算
    4. 预算管理
    5. 税务管理

- #### 系统管理模块
    1. 用户权限管理
    2. 系统日志管理
    3. 数据备份与恢复
    4. 系统设置
    5. 系统更新与维护

--- 

### 超市管理系统模块详述

#### 商品管理模块

##### 商品信息录入

1. 核心属性：

- 基础信息：商品ID、名称、条码（ISBN/UPC）、规格（单位/重量/体积）
- 业务属性：分类、供应商、安全库存、保质期（需支持不同计量单位）
- 扩展属性：商品描述、主图URL

2. 特殊需求：

1.️ 条码唯一性校验（实时校验）
2.️ 保质期商品提前30天预警

3. 技术实现方案
- 数据库表单设计

##### 商品分类管理
##### 商品库存管理
##### 商品价格管理
##### 促销活动管理

- #### 会员管理模块
    1. 会员信息录入
    2. 会员等级查询
    3. 积分政策管理
    4. 会员消费记录管理
    5. 会员积分兑换管理
