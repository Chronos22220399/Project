#!/bin/bash

# 检查 yay 是否已安装
if command -v yay >/dev/null 2>&1; then
  echo "yay 已安装，跳过安装步骤。"
  exit 0
fi

echo "开始安装 yay-bin ..."

# 克隆 yay-bin 并构建安装
git clone https://aur.archlinux.org/yay-bin.git && \
  cd yay-bin && \
  makepkg -si --noconfirm --skippgpcheck

# 清理安装目录
cd .. && rm -rf yay-bin

echo "yay 安装完成。"
