#!/bin/bash

cd /app/SuperMarketManagementSystem/third_party/

# 检查 crow 是否已存在
if ! ls ./ | grep -q crow; then
  echo "third_party 中不存在 crow, 开始获取 crow"

  # 优先使用 yay 安装 crow（如存在）
  if command -v yay >/dev/null 2>&1; then
    echo "检测到 yay，尝试使用 yay 安装 crow"
    yay -S crow --noconfirm
  else
    echo "未检测到 yay，使用 git clone 构建 crow"

    # 克隆仓库并构建安装
    git clone https://github.com/CrowCpp/Crow.git
    cd Crow
    mkdir build && cd build
    cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF
    make install
  fi
else
  echo "crow 已存在，跳过安装"
fi
