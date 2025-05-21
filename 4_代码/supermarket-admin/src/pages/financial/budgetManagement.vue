<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加预算计划</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="budget_period" label="预算周期" width="120" />
            <el-table-column prop="department_name" label="部门名称" />
            <el-table-column prop="budget_type" label="预算类型" />
            <el-table-column prop="budget_amount" label="预算金额" />
            <el-table-column prop="actual_spent_amount" label="实际支出" />
            <el-table-column prop="status" label="状态" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.budget_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="预算周期">
                    <el-date-picker v-model="form.budget_period" type="month" placeholder="选择月份" />
                </el-form-item>
                <el-form-item label="部门名称">
                    <el-input v-model="form.department_name" />
                </el-form-item>
                <el-form-item label="预算类型">
                    <el-select v-model="form.budget_type" placeholder="选择类型">
                        <el-option label="年度预算" value="年度预算" />
                        <el-option label="临时预算" value="临时预算" />
                        <el-option label="季度预算" value="季度预算" />
                    </el-select>
                </el-form-item>
                <el-form-item label="预算金额">
                    <el-input v-model="form.budget_amount" />
                </el-form-item>
                <el-form-item label="实际支出金额">
                    <el-input v-model="form.actual_spent_amount" />
                </el-form-item>
                <el-form-item label="负责人ID">
                    <el-input v-model="form.responsible_person_id" />
                </el-form-item>
                <el-form-item label="状态">
                    <el-select v-model="form.status" placeholder="选择状态">
                        <el-option label="进行中" value="进行中" />
                        <el-option label="已完成" value="已完成" />
                        <el-option label="超支" value="超支" />
                        <el-option label="未使用" value="未使用" />
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

interface BudgetPlan {
    budget_id: number
    budget_period: string
    department_name: string
    budget_type: string
    budget_amount: number
    actual_spent_amount: number
    create_at: string
    responsible_person_id: number
    status: string
}

const generateFakeBudgetPlans = (): BudgetPlan[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        budget_id: Date.now() + i,
        budget_period: `2025-${(i % 12 + 1).toString().padStart(2, '0')}`,
        department_name: ['市场部', '技术部', '财务部'][i % 3],
        budget_type: ['年度预算', '临时预算', '季度预算'][i % 3],
        budget_amount: Number((Math.random() * 50000).toFixed(2)),
        actual_spent_amount: Number((Math.random() * 48000).toFixed(2)),
        create_at: '2025-05-21',
        responsible_person_id: 1000 + i,
        status: ['进行中', '已完成', '超支', '未使用'][i % 4]
    }))
}

const tableData = ref<BudgetPlan[]>(generateFakeBudgetPlans())
const currentPage = ref(1)
const pageSize = ref(5)
const dialogVisible = ref(false)
const dialogTitle = ref('添加预算计划')
const form = ref<Partial<BudgetPlan>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: BudgetPlan) => {
    dialogTitle.value = row ? '编辑预算计划' : '添加预算计划'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.budget_id) {
        const index = tableData.value.findIndex(item => item.budget_id === form.value.budget_id)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as BudgetPlan) }
        }
    } else {
        const newRecord: BudgetPlan = {
            ...(form.value as BudgetPlan),
            budget_id: Date.now(),
            create_at: new Date().toISOString().slice(0, 10)
        }
        tableData.value.push(newRecord)
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.budget_id !== id)
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
