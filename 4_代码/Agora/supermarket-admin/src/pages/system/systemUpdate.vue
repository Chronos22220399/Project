<template>
    <div class="system-update">
        <el-card>
            <div class="form-area">
                <el-button type="success" @click="checkForUpdates">检查更新</el-button>
                <el-button type="danger" @click="performMaintenance">执行维护</el-button>
            </div>
        </el-card>
    </div>
</template>

<script setup>
const checkForUpdates = () => {
    console.log('正在检查系统更新');
};

const performMaintenance = () => {
    console.log('正在进行系统维护');
};
</script>

<style scoped>
.system-update {
    padding: 20px;
}

.form-area {
    text-align: center;
}
</style>