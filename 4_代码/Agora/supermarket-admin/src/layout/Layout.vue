<script setup lang="ts">
import Navbar from './Navbar.vue';
import Sidebar from './Sidebar.vue';
</script>

<template>
    <div class="layout-wrapper">
        <el-container>
            <!-- 侧边栏 -->
            <el-aside width="200px">
                <Sidebar />
            </el-aside>

            <el-container>
                <!-- 顶部导航栏 -->
                <el-header>
                    <Navbar />
                </el-header>

                <!-- 主内容区 -->
                <el-main>
                    <router-view />
                </el-main>
            </el-container>
        </el-container>
    </div>
</template>

<style scoped>
.el-header {
    background: #fff;
    box-shadow: 0px 2px 5px rgba(0, 0, 0, 0.1);
    padding: 10px;
}
</style>

<style>
.layout-wrapper {
    min-height: 100vh;
    /* background-image: url('../components/layout/goods.jpg'); */
    background-size: cover;
    background-repeat: no-repeat;
    background-position: center center;
}
</style>
