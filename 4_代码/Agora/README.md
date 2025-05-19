## 用法

### 初始化
使用 `./init.sh` 创建并启动镜像，支持在 arm64、arm64 架构的机器上运行，镜像中的环境会自动配置

#### 退出容器后重新打开容器
使用 `./start.sh` 可在退出容器后重新启动并进入容器

#### 安装第三方库
通过 `./install-all.sh` 能自动安装所需的第三方库
> ⚠️install-all.sh 已暂停更新，不能保证能安装好所有库，但需要手动编译安装的库已配置好了，无需担心，若有需要的库未被安装，请自行通过 pacman、yay 或 paru 安装，如有疑问，请自行解决。

#### 启动服务
通过 `./run.sh` 可直接启动服务

#### 服务内的脚本
服务内的脚本存放于 `SupermarketManageMentSystem/scripts` 下，其中存放有：
1. code_gen.py：根据 `sql` 下的 ddl 文件生成初始化子模块所需文件
2. create_all_tables.py：读取 `sql` 下所有 ddl 文件生成 `sqlpp11` 所需的头文件
2. create_single_table.py：读取 `sql` 下指定的 ddl 文件生成 `sqlpp11` 所需的头文件

