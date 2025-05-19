<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加工资记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="记录ID" width="80" />
            <el-table-column prop="employeeId" label="员工ID" width="100" />
            <el-table-column prop="employeeName" label="员工姓名" />
            <el-table-column prop="baseSalary" label="基本工资" />
            <el-table-column prop="bonus" label="奖金" />
            <el-table-column prop="deductions" label="扣款" />
            <el-table-column prop="actualSalary" label="实发工资" />
            <el-table-column prop="payDate" label="发放日期" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="员工ID"><el-input v-model="form.employeeId" /></el-form-item>
                <el-form-item label="员工姓名"><el-input v-model="form.employeeName" /></el-form-item>
                <el-form-item label="基本工资"><el-input-number v-model="form.baseSalary" :min="0" /></el-form-item>
                <el-form-item label="奖金"><el-input-number v-model="form.bonus" :min="0" /></el-form-item>
                <el-form-item label="扣款"><el-input-number v-model="form.deductions" :min="0" /></el-form-item>
                <el-form-item label="发放日期">
                    <el-date-picker v-model="form.payDate" type="date" placeholder="选择日期" />
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

interface Salary {
    id: number
    employeeId: string
    employeeName: string
    baseSalary: number
    bonus: number
    deductions: number
    actualSalary: number
    payDate: string
}

const generateFakeSalaries = (): Salary[] => {
    const names = ['张三', '李四', '王五', '赵六', '钱七']
    return Array.from({ length: 50 }, (_, i) => {
        const base = 5000 + i * 10
        const bonus = (i % 5) * 100
        const deductions = (i % 3) * 50
        return {
            id: i + 1,
            employeeId: 'EMP' + (1000 + i),
            employeeName: names[i % names.length],
            baseSalary: base,
            bonus,
            deductions,
            actualSalary: base + bonus - deductions,
            payDate: `2025-05-${(i % 28 + 1).toString().padStart(2, '0')}`,
        }
    })
}

const tableData = ref<Salary[]>(generateFakeSalaries())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加工资记录')
const form = ref<Partial<Salary>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

watch(form, (val) => {
    if (val.baseSalary !== undefined && val.bonus !== undefined && val.deductions !== undefined) {
        form.value.actualSalary = val.baseSalary + val.bonus - val.deductions
    }
}, { deep: true })

const openDialog = (row?: Salary) => {
    dialogTitle.value = row ? '编辑工资记录' : '添加工资记录'
    form.value = row ? { ...row } : {
        baseSalary: 0,
        bonus: 0,
        deductions: 0,
        actualSalary: 0,
    }
    dialogVisible.value = true
}

const handleSave = async () => {
    const newData = { ...form.value }
    try {
        if (form.value.id) {
            await axios.put(`/api/salary/${form.value.id}`, newData)
            const index = tableData.value.findIndex(item => item.id === form.value.id)
            if (index !== -1) tableData.value[index] = form.value as Salary
        } else {
            const response = await axios.post('/api/salary', newData)
            const newId = response.data.id || Date.now()
            tableData.value.push({ ...(form.value as Salary), id: newId })
        }
        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/salary/${id}`)
        tableData.value = tableData.value.filter(item => item.id !== id)
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
