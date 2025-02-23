### 目录内容介绍
1. cmake/ 存放 cmake 配置文件
2. first/ 当前的测试子项目
3. scripts/ 项目的脚本目录，其内存放cmake第三方库配置脚本、根据 ddl 生成数据库、orm 类头文件的脚本、项目初始化脚本等
4. CMakeLists.txt 根目录的 cmake 管理项，内部存放子项目的公共配置项
5. libraries.json 使用的第三方库的配置文件
6. run.sh 项目编译脚本(限制于 unix 类系统)

### 注意
项目当前未设置数据库文件的自动查找，因此在不同上下文环境下可能会存在行为不一致，因此当前需要自行寻找编译后的二进制的相对位置，
并据此更改 get_pool_conn_ptr 中的 config 的 path_to_database 的值（当前 path_to_database 的值依赖于 main 函数的传入值，后续会采用
单例模式并处理掉此依赖）。
