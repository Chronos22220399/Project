<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加工资记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="payroll_id" label="记录ID" width="80" />
            <el-table-column prop="employee_id" label="员工ID" width="100" />
            <el-table-column prop="pay_period" label="工资周期" />
            <el-table-column prop="basic_salary" label="基本工资" />
            <el-table-column prop="bonus" label="奖金" />
            <el-table-column prop="deduction" label="扣款" />
            <el-table-column prop="net_salary" label="实发工资" />
            <el-table-column prop="paid_at" label="发放时间" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.payroll_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="员工ID"><el-input v-model="form.employee_id" /></el-form-item>
                <el-form-item label="工资周期"><el-input v-model="form.pay_period" /></el-form-item>
                <el-form-item label="基本工资"><el-input-number v-model="form.basic_salary" :min="0" /></el-form-item>
                <el-form-item label="奖金"><el-input-number v-model="form.bonus" :min="0" /></el-form-item>
                <el-form-item label="扣款"><el-input-number v-model="form.deduction" :min="0" /></el-form-item>
                <el-form-item label="发放时间">
                    <el-date-picker v-model="form.paid_at" type="date" placeholder="选择日期" />
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
import { ref, computed, watch } from 'vue'
import axios from 'axios'

interface Payroll {
    payroll_id: number
    employee_id: string
    pay_period: string
    basic_salary: number
    bonus: number
    deduction: number
    net_salary: number
    paid_at: string
}

const generateFakePayrolls = (): Payroll[] => {
    const periods = ['2025-04', '2025-05', '2025-06']
    return Array.from({ length: 50 }, (_, i) => {
        const basic = 5000 + i * 10
        const bonus = (i % 5) * 100
        const deduction = (i % 3) * 50
        return {
            payroll_id: i + 1,
            employee_id: 'EMP' + (1000 + i),
            pay_period: periods[i % periods.length],
            basic_salary: basic,
            bonus,
            deduction,
            net_salary: basic + bonus - deduction,
            paid_at: `2025-05-${(i % 28 + 1).toString().padStart(2, '0')}`
        }
    })
}

const tableData = ref<Payroll[]>(generateFakePayrolls())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加工资记录')
const form = ref<Partial<Payroll>>({ basic_salary: 0, bonus: 0, deduction: 0, net_salary: 0 })

watch(form, (val) => {
    if (val.basic_salary !== undefined && val.bonus !== undefined && val.deduction !== undefined) {
        form.value.net_salary = val.basic_salary + val.bonus - val.deduction
    }
}, { deep: true })

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: Payroll) => {
    dialogTitle.value = row ? '编辑工资记录' : '添加工资记录'
    form.value = row ? { ...row } : { basic_salary: 0, bonus: 0, deduction: 0, net_salary: 0 }
    dialogVisible.value = true
}

const handleSave = async () => {
    const newData = { ...form.value }
    try {
        if (form.value.payroll_id) {
            await axios.put(`/api/payroll/${form.value.payroll_id}`, newData)
            const index = tableData.value.findIndex(item => item.payroll_id === form.value.payroll_id)
            if (index !== -1) tableData.value[index] = form.value as Payroll
        } else {
            const response = await axios.post('/api/payroll', newData)
            const newId = response.data.payroll_id || Date.now()
            tableData.value.push({ ...(form.value as Payroll), payroll_id: newId })
        }
        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/payroll/${id}`)
        tableData.value = tableData.value.filter(item => item.payroll_id !== id)
    } catch (err) {
        console.error('删除失败', err)
    }
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
