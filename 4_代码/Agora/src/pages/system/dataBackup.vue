<template>
    <div class="data-backup-recovery">
        <el-card>
            <div class="form-area">
                <el-button type="primary" @click="backupData">立即备份数据</el-button>
                <el-button type="warning" @click="recoverData">恢复数据</el-button>
            </div>
        </el-card>
    </div>
</template>

<script setup>
const backupData = () => {
    console.log('数据备份已启动');
};

const recoverData = () => {
    console.log('数据恢复已启动');
};
</script>

<style scoped>
.data-backup-recovery {
    padding: 20px;
}

.form-area {
    text-align: center;
}
</style>