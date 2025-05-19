<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加日志</el-button>
        </div>
        <el-table :data="paginatedData" border>
            <el-table-column prop="logId" label="日志ID" width="80" />
            <el-table-column prop="operator" label="操作人" />
            <el-table-column prop="operationType" label="操作类型" />
            <el-table-column prop="content" label="内容" />
            <el-table-column prop="time" label="时间" />
            <el-table-column prop="ipAddress" label="IP地址" />
            <el-table-column prop="macAddress" label="MAC地址" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.logId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="操作人"><el-input v-model="form.operator" /></el-form-item>
                <el-form-item label="操作类型"><el-input v-model="form.operationType" /></el-form-item>
                <el-form-item label="内容"><el-input v-model="form.content" /></el-form-item>
                <el-form-item label="时间"><el-date-picker v-model="form.time" type="datetime" /></el-form-item>
                <el-form-item label="IP地址"><el-input v-model="form.ipAddress" /></el-form-item>
                <el-form-item label="MAC地址"><el-input v-model="form.macAddress" /></el-form-item>
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
    logId: number
    operator: string
    operationType: string
    content: string
    time: string
    ipAddress: string
    macAddress: string
}

const generateFakeLogs = (): SystemLog[] =>
    Array.from({ length: 20 }, (_, i) => ({
        logId: i + 1,
        operator: `admin${i + 1}`,
        operationType: i % 2 ? '修改' : '登录',
        content: '测试操作内容',
        time: '2025-05-01 10:00',
        ipAddress: '192.168.0.' + (i + 1),
        macAddress: `00:0a:95:9d:68:${(10 + i).toString(16)}`
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
    if (form.value.logId) {
        const index = tableData.value.findIndex(item => item.logId === form.value.logId)
        if (index !== -1) tableData.value[index] = form.value as SystemLog
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SystemLog), logId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (logId: number) => {
    tableData.value = tableData.value.filter(item => item.logId !== logId)
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
