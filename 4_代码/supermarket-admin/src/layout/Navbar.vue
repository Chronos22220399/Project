<script setup lang="ts">
import { ref } from 'vue';
import { useRouter } from 'vue-router';

const router = useRouter();
const username = ref("Ess & koi");

// 退出登录
const logout = () => {
    router.push('/login');
};
</script>

<template>
    <div class="header-container">
        <el-row justify="space-between" align="middle" class="header-row">
            <el-col :span="12" class="system-title">
                超市管理系统
            </el-col>
            <el-col :span="12" class="user-info" style="text-align: right;">
                <el-dropdown>
                    <span class="el-dropdown-link">{{ username }}</span>
                    <template #dropdown>
                        <el-dropdown-menu>
                            <el-dropdown-item @click="logout">退出登录</el-dropdown-item>
                        </el-dropdown-menu>
                    </template>
                </el-dropdown>
            </el-col>
        </el-row>
    </div>
</template>

<style scoped>
.header-container {
    width: 100%;
    height: 60px;
    padding: 0 20px;
    background: linear-gradient(to bottom, #f0f4ff, #dde6ff, #d1e0ff);
    display: flex;
    align-items: center;
    box-shadow: 0 2px 6px rgba(0, 0, 0, 0.1);
}

.system-title {
    font-size: 15px;
    font-weight: bolder;
    color: #2c3e50;
    line-height: 60px;
}

.el-dropdown-link {
    cursor: pointer;
    font-weight: bold;
    font-size: 16px;
    color: #333;
    padding: 10px 16px;
    width: 80px;
    transition: background-color 0.3s;
    border-radius: 4px;
    position: relative;
}

.el-dropdown-link:hover {
    background-color: rgba(0, 0, 0, 0.05);
}
</style>
