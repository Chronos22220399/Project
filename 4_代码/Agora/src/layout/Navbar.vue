<script setup lang="ts">
import { ref } from 'vue';
import { useRouter } from 'vue-router';

const router = useRouter();
const username = ref("Admin");

// 退出登录
const logout = () => {
    router.push('/login');
};
</script>

<template>
    <el-row justify="space-between">
        <el-col>超市管理系统</el-col>
        <el-col>
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
</template>

<style scoped>
.el-dropdown-link {
    cursor: pointer;
    font-weight: bold;
}
</style>
