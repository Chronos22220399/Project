<template>
    <el-button class="settings-item" @click="navigate">
        <img src="../assets/setting.webp" alt="齿轮图标" class="settings-icon" />
    </el-button>
</template>

<script setup lang="ts">
import { useRouter } from 'vue-router';

const router = useRouter();

const navigate = () => {
    // 导航到设置页面
    router.push('/settings');
};
</script>

<style scoped>
.settings-icon {
    width: 20px;
    height: 20px;
}

.settings-item {
    display: flex;
    align-items: center;
    padding: 10px;
    cursor: pointer;
}
</style>
