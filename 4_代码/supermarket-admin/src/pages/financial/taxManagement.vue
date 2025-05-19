<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加税务记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="project" label="项目" />
            <el-table-column prop="taxAmount" label="税额" />
            <el-table-column prop="date" label="时间" />
            <el-table-column prop="type" label="类型" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.date)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="项目"><el-input v-model="form.project" /></el-form-item>
                <el-form-item label="税额"><el-input v-model="form.taxAmount" /></el-form-item>
                <el-form-item label="时间"><el-date-picker v-model="form.date" type="date" /></el-form-item>
                <el-form-item label="类型"><el-input v-model="form.type" /></el-form-item>
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

interface TaxRecord {
    project: string
    taxAmount: number
    date: string
    type: string
}

const generateFakeTaxRecords = (): TaxRecord[] => [
    { project: '销售税', taxAmount: 5000, date: '2025-05-01', type: '增值税' },
    { project: '进项税', taxAmount: 3000, date: '2025-05-05', type: '增值税' },
    { project: '企业所得税', taxAmount: 7000, date: '2025-05-10', type: '所得税' },
    { project: '个人所得税', taxAmount: 2000, date: '2025-05-15', type: '所得税' }
]

const tableData = ref < TaxRecord[] > (generateFakeTaxRecords())
const currentPage = ref(1)
const pageSize = ref(5)
const dialogVisible = ref(false)
const dialogTitle = ref('添加税务记录')
const form = ref < Partial < TaxRecord >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: TaxRecord) => {
    dialogTitle.value = row ? '编辑税务记录' : '添加税务记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.date) {
        const index = tableData.value.findIndex(item => item.date === form.value.date && item.project === form.value.project)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as TaxRecord) }
        } else {
            tableData.value.push(form.value as TaxRecord)
        }
    }
    dialogVisible.value = false
}

const handleDelete = (date: string) => {
    tableData.value = tableData.value.filter(item => item.date !== date)
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
