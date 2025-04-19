#! bin/bash
set -e

# check whether git exists
if ! command -v git &> /dev/null; then
  echo "Git does not exists, please install it by pacman now"  
  exit 1
fi

cd third_party
if [ ! -D "sqlpp11" ]; then
  git clone https://github.com/rbock/sqlpp11.git
fi

# installed sqlpp11 by hand
cd sqlpp11
cmake -B build \
  -DBUILD_SQLITE3_CONNECTOR=ON \
  -DBUILD_MYSQL_CONNECTOR=ON \
  -DDEPENDENCY_CHECK=OFF \
  -BUILD_TESTING=OFF

cmake --build build --parallel $(nproc) --target install
