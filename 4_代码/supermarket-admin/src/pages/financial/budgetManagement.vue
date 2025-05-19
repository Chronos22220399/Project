<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加预算记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="month" label="月份" width="100" />
            <el-table-column prop="projectName" label="项目名称" />
            <el-table-column prop="budgetAmount" label="预算金额" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.month)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="月份"><el-date-picker v-model="form.month" type="month"
                        placeholder="选择月份" /></el-form-item>
                <el-form-item label="项目名称"><el-input v-model="form.projectName" /></el-form-item>
                <el-form-item label="预算金额"><el-input v-model="form.budgetAmount" /></el-form-item>
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

interface BudgetRecord {
    month: string
    projectName: string
    budgetAmount: number
}

const generateFakeBudget = (): BudgetRecord[] => [
    { month: '2025-01', projectName: '营销活动', budgetAmount: 20000 },
    { month: '2025-02', projectName: '设备维护', budgetAmount: 15000 },
    { month: '2025-03', projectName: '新产品开发', budgetAmount: 25000 },
    { month: '2025-04', projectName: '员工培训', budgetAmount: 12000 },
    { month: '2025-05', projectName: '市场调研', budgetAmount: 18000 }
]

const tableData = ref < BudgetRecord[] > (generateFakeBudget())
const currentPage = ref(1)
const pageSize = ref(5)
const dialogVisible = ref(false)
const dialogTitle = ref('添加预算记录')
const form = ref < Partial < BudgetRecord >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: BudgetRecord) => {
    dialogTitle.value = row ? '编辑预算记录' : '添加预算记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.month) {
        const index = tableData.value.findIndex(item => item.month === form.value.month && item.projectName === form.value.projectName)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as BudgetRecord) }
        } else {
            tableData.value.push(form.value as BudgetRecord)
        }
    }
    dialogVisible.value = false
}

const handleDelete = (month: string) => {
    tableData.value = tableData.value.filter(item => item.month !== month)
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
