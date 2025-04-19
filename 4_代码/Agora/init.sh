#! /bin/bash

if ! command -v docker &> /dev/null; then
  echo "Docker does not found, Please check whether installed it or started"
  exit 1
fi

# check the device's system
OS_TYPE="$(uname)"

# if is pure linux and has group docker, then execute `newgrp docker` to avoid `sudo`
if [[ "$OS_TYPE" != "Darwin" ]] && ! grep -qEi "(Microsoft|WSL)" /proc/version 2> /dev/null; then
# add current user to docker group temporarily
  echo "is not apple"
  getent group docker > /dev/null 2>&1 && newgrp docker
fi

ARCH=$(arch)

#
if [[ "$ARCH" == "arm64" || "$ARCH" == "aarch64" ]]; then
  echo "检测到设备为 arm64(aarch64) 架构，已自动作出更改"
  docker build -f ./Dockerfile.arm64 --network host -t supermarket-builder . 
elif [[ "$ARCH" == "x86_64" || "$ARCH" == "amd64" ]]; then
  docker build -f ./Dockerfile.amd64 --network host -t supermarket-builder .
fi

docker run -it --rm supermarket-builder
