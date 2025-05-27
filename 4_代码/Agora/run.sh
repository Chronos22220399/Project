#!/bin/bash

if_exists_then_run() { local target="$1"  # 改为使用第一个输入参数

    if [ -f "$target" ]; then
        echo "➔ 检测到测试可执行文件，开始运行..."
        "$target"
        return $?  # 返回执行程序的退出码
    else
        echo "✗ 错误：未找到可执行文件 $target" >&2
        echo "请确认以下步骤已执行："
        echo "1. 已运行 CMake 配置（-DEnableTest=ON）"
        echo "2. 已完成项目编译"
        return 1
    fi
}

cmake -DEnableTest=OFF -S . -B build -G Ninja # default turn off unit test

ARCH=$(uname -m)

case "$ARCH" in
    x86_64|amd64) cmake --build build --parallel $(nproc);;
  arm64|aarch64) cmake --build build --parallel 16 ;;
  *) echo "未知架构: $ARCH"; exit 1 ;;
esac

# cd build/SuperMarketManagementSystem && ctest
<<<<<<< HEAD
#echo "开始测试 jwt_manager_test"
#if_exists_then_run "./build/SuperMarketManagementSystem/jwt_manager_test" || exit 1
#echo "\n"
#
#echo "开始测试 vcode_manager_test"
#if_exists_then_run "./build/SuperMarketManagementSystem/vcode_manager_test" || exit 1
#echo "\n"
=======
# echo "开始测试 jwt_manager_test"
# if_exists_then_run "./build/SuperMarketManagementSystem/jwt_manager_test" || exit 1
# echo "\n"
#
# echo "开始测试 vcode_manager_test"
# if_exists_then_run "./build/SuperMarketManagementSystem/vcode_manager_test" || exit 1
# echo "\n"
>>>>>>> fcef6cda48b099c3326962bf1af39fe701693d4f

echo "开始运行服务"
if_exists_then_run ./build/SuperMarketManagementSystem/SuperMarketManagementSystem || exit 1
echo "\n"
