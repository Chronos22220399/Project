<template>
    <div class="system-logs">
        <el-card>
            <div class="log-list">
                <el-table :data="logs" border>
                    <el-table-column label="日志类型" prop="type" />
                    <el-table-column label="日志内容" prop="content" />
                    <el-table-column label="发生时间" prop="timestamp" />
                </el-table>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const logs = ref([
    { type: '系统启动', content: '系统成功启动', timestamp: '2025-05-01 08:00' },
    { type: '用户登录', content: '用户 admin 登录', timestamp: '2025-05-01 08:15' },
    { type: '错误', content: '数据库连接失败', timestamp: '2025-05-01 08:30' },
]);

</script>

<style scoped>
.system-logs {
    padding: 20px;
}

.log-list {
    max-width: 800px;
    margin: 0 auto;
}
</style>