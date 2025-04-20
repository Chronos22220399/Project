#! bin/bash
cd /app/SuperMarketManagementSystem/third_party/

# 设置 SQLite3 路径（Arch Linux 实际路径）
export SQLITE3_INCLUDE_DIR=/usr/include
export SQLITE3_LIBRARY=/usr/lib/libsqlite3.so

# 设置 MariaDB 路径（Arch Linux 实际路径）
export MYSQL_INCLUDE_DIR=/usr/include/mysql
export MYSQL_LIBRARY=/usr/lib/libmariadb.so

if ! ls ./ | grep sqlpp11 > /dev/null 2>&1; then
  echo "third_party 中不存在 sqlpp11, 开始获取 sqlpp11"
  # 克隆仓库
  # git submodule add https://github.com/HowardHinnant/date.git ./SuperMarketManagementSystem/third_party/date
  git clone https://github.com/rbock/sqlpp11.git
fi

cd sqlpp11

# 创建构建目录
mkdir -p build && cd build

# 配置 CMake（修复参数语法）
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DSQLITE3_INCLUDE_DIR=${SQLITE3_INCLUDE_DIR} \
  -DSQLITE3_LIBRARY=${SQLITE3_LIBRARY} \
  -DMYSQL_INCLUDE_DIR=${MYSQL_INCLUDE_DIR} \
  -DMYSQL_LIBRARY=${MYSQL_LIBRARY} \
  -DBUILD_SQLITE3_CONNECTOR=ON \
  -DBUILD_MYSQL_CONNECTOR=ON \
  -DDEPENDENCY_CHECK=OFF \
  -DBUILD_TESTING=OFF  # 修复缺少的 "-D"

# 编译并安装
cmake --build . --parallel $(nproc)
cmake --install .
