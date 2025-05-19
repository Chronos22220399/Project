<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="version" label="系统版本" width="120" />
            <el-table-column prop="updateTime" label="更新时间" width="180" />
            <el-table-column prop="content" label="更新内容" />
            <el-table-column prop="maintainer" label="维护人" width="120" />
            <el-table-column prop="status" label="状态" width="100">
                <template #default="scope">
                    <el-tag :type="scope.row.status === '已完成' ? 'success' : 'warning'">{{ scope.row.status }}</el-tag>
                </template>
            </el-table-column>
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="90px">
                <el-form-item label="系统版本"><el-input v-model="form.version" /></el-form-item>
                <el-form-item label="更新时间"><el-date-picker v-model="form.updateTime" type="datetime" /></el-form-item>
                <el-form-item label="更新内容"><el-input v-model="form.content" type="textarea" /></el-form-item>
                <el-form-item label="维护人"><el-input v-model="form.maintainer" /></el-form-item>
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

interface Maintenance {
    id: number
    version: string
    updateTime: string
    content: string
    maintainer: string
    status: string
}

const tableData = ref < Maintenance[] > (Array.from({ length: 6 }, (_, i) => ({
    id: i + 1,
    version: `v1.0.${i}`,
    updateTime: `2025-05-1${i} 10:00:00`,
    content: `优化模块性能，修复若干BUG，添加新功能${i + 1}`,
    maintainer: `维护员${i + 1}`,
    status: i % 2 === 0 ? '已完成' : '进行中'
})))

const currentPage = ref(1)
const pageSize = ref(5)
const dialogVisible = ref(false)
const dialogTitle = ref('添加记录')
const form = ref < Partial < Maintenance >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: Maintenance) => {
    dialogTitle.value = row ? '编辑记录' : '添加记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.id) {
        const index = tableData.value.findIndex(item => item.id === form.value.id)
        if (index !== -1) tableData.value[index] = { ...(form.value as Maintenance) }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as Maintenance), id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.id !== id)
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
