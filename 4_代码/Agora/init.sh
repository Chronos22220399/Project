#!/bin/bash

./scripts/docker-check.sh

# 定义容器名和镜像名
CONTAINER_NAME="supermarket-builder"
IMAGE_NAME="supermarket-builder"

# 清理旧容器
if docker ps -a --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
  echo "发现已存在的容器 ${CONTAINER_NAME}，正在清理..."
  docker stop ${CONTAINER_NAME} > /dev/null 2>&1
  docker rm ${CONTAINER_NAME} > /dev/null 2>&1
fi

# 清理旧镜像
if docker image inspect ${IMAGE_NAME}:latest > /dev/null 2>&1; then
  echo "清理旧镜像 ${IMAGE_NAME}:latest..."
  docker rmi ${IMAGE_NAME}:latest > /dev/null 2>&1
fi

# 替代 arch 命令：使用 uname -m 获取架构
ARCH=$(uname -m)

# 标准化架构名称
case "$ARCH" in
  x86_64|amd64) DOCKERFILE="Dockerfile.amd64";;
  arm64|aarch64) DOCKERFILE="Dockerfile.arm64" ;;
  *) echo "未知架构: $ARCH"; exit 1 ;;
esac

# 构建镜像
echo "检测到设备为 $ARCH 架构，使用 $DOCKERFILE 构建镜像"
if ! docker build -f ./${DOCKERFILE} --network host -t ${IMAGE_NAME}:latest .; then
  echo "构建镜像失败，请检查错误日志"
  exit 1
fi

# 运行容器
echo "启动容器 ${CONTAINER_NAME}..."
docker run -it --name ${CONTAINER_NAME} ${IMAGE_NAME}:latest
