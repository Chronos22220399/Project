#! /bin/bash

./scripts/docker-check.sh

# 定义容器名和镜像名
CONTAINER_NAME="supermarket-builder"
IMAGE_NAME="supermarket-builder"

docker start ${IMAGE_NAME}

docker exec -it ${CONTAINER_NAME} bash
