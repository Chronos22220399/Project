#!/bin/bash


# 检查 fmt 是否已存在
if ! ls /usr/local/include | grep -q jwt-cpp; then
  echo "third_party 中不存在 crow, 开始获取 cr"

  # 优先使用 yay 安装 crow（如存在）
  if command -v yay >/dev/null 2>&1; then
    echo "检测到 yay，尝试使用 yay 安装 crow"
    yay -S crow --noconfirm
  else
    echo "未检测到 yay，使用 git clone 构建 crow"

    cd /tmp
    # 克隆仓库并构建安装
    git clone https://github.com/Thalhammer/jwt-cpp.git
    cd jwt-cpp
    mkdir build && cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local -DJWT_CPP_BUILD_EXAMPLES=OFF -DJWT_CPP_BUILD_TESTS=OFF
    sudo make install
    cd -
  fi
else
  echo "crow 已存在，跳过安装"
fi
