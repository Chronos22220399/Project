#! bin/bash

cd /app/SuperMarketManagementSystem/third_party/

if ! ls ./ | grep crow > /dev/null 2>&1; then
  echo "third_party 中不存在 crow, 开始获取 crow"
  # 克隆仓库
  git clone https://github.com/CrowCpp/Crow.git
fi

cd Crow
mkdir build && cd build 
cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF \
make install
