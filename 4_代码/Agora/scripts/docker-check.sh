#! /bin/bash

# 检查 Docker 是否存在
if ! command -v docker &> /dev/null; then
  echo "Docker 未安装或未启动，请检查 Docker 状态！"
  exit 1
fi

# 检查操作系统类型
OS_TYPE="$(uname)"

# 如果是 Linux（非 WSL 和 macOS），且用户不在 docker 组中，提示需要权限
if [[ "$OS_TYPE" != "Darwin" ]] && ! grep -qEi "(Microsoft|WSL)" /proc/version 2> /dev/null; then
  echo "检测到宿主机为 Linux 系统"
  if ! id -nG "$USER" | grep -qw "docker"; then
    echo "当前用户未加入 docker 组，请手动执行以下命令并重新登录："
    echo "  sudo usermod -aG docker $USER"
    exit 1
  fi
fi
