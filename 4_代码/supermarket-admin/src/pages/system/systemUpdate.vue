<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加记录</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="version" label="版本号" width="120" />
            <el-table-column prop="updateType" label="更新类型" width="120" />
            <el-table-column prop="updatedAt" label="更新时间" width="180" />
            <el-table-column prop="maintainer" label="维护人" width="120" />
            <el-table-column prop="changeSummary" label="变更摘要" />
            <el-table-column prop="status" label="状态" width="100">
                <template #default="scope">
                    <el-tag :type="scope.row.status === '已完成' ? 'success' : 'warning'">
                        {{ scope.row.status }}
                    </el-tag>
                </template>
            </el-table-column>
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.updateId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="版本号"><el-input v-model="form.version" /></el-form-item>
                <el-form-item label="更新类型">
                    <el-select v-model="form.updateType" placeholder="请选择类型">
                        <el-option label="补丁" value="patch" />
                        <el-option label="升级" value="upgrade" />
                        <el-option label="配置变更" value="config" />
                    </el-select>
                </el-form-item>
                <el-form-item label="更新时间">
                    <el-date-picker v-model="form.updatedAt" type="datetime" />
                </el-form-item>
                <el-form-item label="维护人"><el-input v-model="form.maintainer" /></el-form-item>
                <el-form-item label="摘要"><el-input v-model="form.changeSummary" type="textarea" /></el-form-item>
                <el-form-item label="更新说明"><el-input v-model="form.description" type="textarea" /></el-form-item>
                <el-form-item label="影响模块"><el-input v-model="form.affectedModules" type="textarea" /></el-form-item>
                <el-form-item label="状态">
                    <el-select v-model="form.status" placeholder="请选择状态">
                        <el-option label="已完成" value="已完成" />
                        <el-option label="进行中" value="进行中" />
                    </el-select>
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

interface SystemUpdateLog {
    updateId: number
    version: string
    updateType: string
    updatedAt: string
    userId: number
    maintainer: string
    description: string
    changeSummary: string
    affectedModules: string
    status: string
}

const tableData = ref<SystemUpdateLog[]>(Array.from({ length: 6 }, (_, i) => ({
    updateId: i + 1,
    version: `v1.0.${i}`,
    updateType: i % 2 === 0 ? 'patch' : 'upgrade',
    updatedAt: `2025-05-1${i} 10:00:00`,
    userId: 1000 + i,
    maintainer: `维护员${i + 1}`,
    description: `系统优化与安全修复更新内容${i + 1}`,
    changeSummary: `修复Bug，性能提升${i + 1}`,
    affectedModules: `模块A、模块B`,
    status: i % 2 === 0 ? '已完成' : '进行中'
})))

const currentPage = ref(1)
const pageSize = ref(5)
const dialogVisible = ref(false)
const dialogTitle = ref('添加记录')
const form = ref<Partial<SystemUpdateLog>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SystemUpdateLog) => {
    dialogTitle.value = row ? '编辑记录' : '添加记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.updateId) {
        const index = tableData.value.findIndex(item => item.updateId === form.value.updateId)
        if (index !== -1) tableData.value[index] = { ...(form.value as SystemUpdateLog) }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SystemUpdateLog), updateId: newId, userId: 999 })
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.updateId !== id)
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
