<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加配置</el-button>
        </div>

        <el-table :data="paginatedData" border>
            <el-table-column prop="setting_key" label="配置键" />
            <el-table-column prop="setting_value" label="配置值" />
            <el-table-column prop="description" label="描述" />
            <el-table-column prop="updated_at" label="最后修改时间" />
            <el-table-column prop="user_id" label="修改人ID" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.setting_key)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="配置键"><el-input v-model="form.setting_key" :disabled="isEdit" /></el-form-item>
                <el-form-item label="配置值"><el-input v-model="form.setting_value" /></el-form-item>
                <el-form-item label="描述"><el-input v-model="form.description" /></el-form-item>
                <el-form-item label="修改人ID"><el-input v-model="form.user_id" /></el-form-item>
                <el-form-item label="修改时间">
                    <el-date-picker v-model="form.updated_at" type="datetime" style="width: 100%;" />
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

interface SystemSetting {
    setting_key: string
    setting_value: string
    description: string
    updated_at: string
    user_id: string
}

const tableData = ref<SystemSetting[]>([
    {
        setting_key: 'language',
        setting_value: 'zh',
        description: '系统默认语言',
        updated_at: '2025-05-21 10:00:00',
        user_id: 'admin1'
    },
    {
        setting_key: 'storage_path',
        setting_value: '/data/storage',
        description: '数据存储路径',
        updated_at: '2025-05-20 15:30:00',
        user_id: 'admin2'
    }
])

const currentPage = ref(1)
const pageSize = ref(5)
const dialogVisible = ref(false)
const dialogTitle = ref('添加配置')
const form = ref<Partial<SystemSetting>>({})
const isEdit = ref(false)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SystemSetting) => {
    dialogTitle.value = row ? '编辑配置' : '添加配置'
    isEdit.value = !!row
    form.value = row ? { ...row } : { updated_at: new Date().toISOString() }
    dialogVisible.value = true
}

const handleSave = () => {
    const index = tableData.value.findIndex(item => item.setting_key === form.value.setting_key)
    if (index !== -1) {
        tableData.value[index] = form.value as SystemSetting
    } else {
        tableData.value.push(form.value as SystemSetting)
    }
    dialogVisible.value = false
}

const handleDelete = (key: string) => {
    tableData.value = tableData.value.filter(item => item.setting_key !== key)
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
