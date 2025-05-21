<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加日志</el-button>
        </div>
        <el-table :data="paginatedData" border>
            <el-table-column prop="log_id" label="日志ID" width="80" />
            <el-table-column prop="user_id" label="用户ID" />
            <el-table-column prop="action_type" label="操作类型" />
            <el-table-column prop="actual_detail" label="操作内容" />
            <el-table-column prop="timestamp" label="操作时间" />
            <el-table-column prop="ip_address" label="IP地址" />
            <el-table-column prop="mac_address" label="MAC地址" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.log_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="用户ID">
                    <el-input v-model="form.user_id" />
                </el-form-item>
                <el-form-item label="操作类型">
                    <el-input v-model="form.action_type" />
                </el-form-item>
                <el-form-item label="操作内容">
                    <el-input v-model="form.actual_detail" />
                </el-form-item>
                <el-form-item label="操作时间">
                    <el-date-picker v-model="form.timestamp" type="datetime" />
                </el-form-item>
                <el-form-item label="IP地址">
                    <el-input v-model="form.ip_address" />
                </el-form-item>
                <el-form-item label="MAC地址">
                    <el-input v-model="form.mac_address" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSave">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'

interface SystemLog {
    log_id: number
    user_id: string
    action_type: string
    actual_detail: string
    timestamp: string
    ip_address: string
    mac_address: string
}

const generateFakeLogs = (): SystemLog[] =>
    Array.from({ length: 50 }, (_, i) => ({
        log_id: i + 1,
        user_id: `admin${i + 1}`,
        action_type: i % 2 ? '修改' : '登录',
        actual_detail: '模拟操作内容',
        timestamp: '2025-05-01 10:00',
        ip_address: '192.168.0.' + (i + 1),
        mac_address: `00:0a:95:9d:68:${(10 + i).toString(16)}`
    }))

const tableData = ref<SystemLog[]>(generateFakeLogs())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加日志')
const form = ref<Partial<SystemLog>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SystemLog) => {
    dialogTitle.value = row ? '编辑日志' : '添加日志'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.log_id) {
        const index = tableData.value.findIndex(item => item.log_id === form.value.log_id)
        if (index !== -1) tableData.value[index] = form.value as SystemLog
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SystemLog), log_id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (log_id: number) => {
    tableData.value = tableData.value.filter(item => item.log_id !== log_id)
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
