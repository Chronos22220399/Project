<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加员工</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="员工ID" width="100" />
            <el-table-column prop="name" label="姓名" />
            <el-table-column prop="gender" label="性别" />
            <el-table-column prop="phone" label="电话" />
            <el-table-column prop="email" label="邮箱" />
            <el-table-column prop="department" label="部门" />
            <el-table-column prop="position" label="岗位" />
            <el-table-column prop="entryDate" label="入职日期" />
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
            <el-form :model="form" label-width="90px">
                <el-form-item label="姓名"><el-input v-model="form.name" /></el-form-item>
                <el-form-item label="性别">
                    <el-select v-model="form.gender" placeholder="选择性别">
                        <el-option label="男" value="男" />
                        <el-option label="女" value="女" />
                    </el-select>
                </el-form-item>
                <el-form-item label="电话"><el-input v-model="form.phone" /></el-form-item>
                <el-form-item label="邮箱"><el-input v-model="form.email" /></el-form-item>
                <el-form-item label="部门"><el-input v-model="form.department" /></el-form-item>
                <el-form-item label="岗位"><el-input v-model="form.position" /></el-form-item>
                <el-form-item label="入职日期"><el-date-picker v-model="form.entryDate" type="date" /></el-form-item>
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
import axios from 'axios'

interface Employee {
    id: number
    name: string
    gender: string
    phone: string
    email: string
    department: string
    position: string
    entryDate: string
}

// 生成假数据
const generateFakeEmployees = () => {
    const genders = ['男', '女']
    const departments = ['销售部', '技术部', '财务部', '人事部']
    const positions = ['经理', '主管', '职员']
    return Array.from({ length: 50 }, (_, i) => ({
        id: i + 1,
        name: `员工${i + 1}`,
        gender: genders[Math.floor(Math.random() * genders.length)],
        phone: `13${Math.floor(Math.random() * 1000000000)}`,
        email: `employee${i + 1}@example.com`,
        department: departments[Math.floor(Math.random() * departments.length)],
        position: positions[Math.floor(Math.random() * positions.length)],
        entryDate: `2023-${String(Math.floor(Math.random() * 12) + 1).padStart(2, '0')}-${String(Math.floor(Math.random() * 28) + 1).padStart(2, '0')}`
    }))
}

const tableData = ref < Employee[] > (generateFakeEmployees())
const dialogVisible = ref(false)
const dialogTitle = ref('添加员工')
const form = ref < Partial < Employee >> ({})

// 分页
const currentPage = ref(1)
const pageSize = ref(10)
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

// 打开对话框
const openDialog = (row?: Employee) => {
    dialogTitle.value = row ? '编辑员工' : '添加员工'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

// 保存
const handleSave = async () => {
    const employeeData = { ...form.value }

    try {
        let response
        if (form.value.id) {
            response = await axios.put(`/api/employee/${form.value.id}`, employeeData)
            const index = tableData.value.findIndex(emp => emp.id === form.value.id)
            if (index !== -1) tableData.value[index] = form.value as Employee
        } else {
            response = await axios.post('/api/employee', employeeData)
            const newId = response.data.id || Date.now()
            tableData.value.push({ ...(form.value as Employee), id: newId })
        }

        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

// 删除
const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/employee/${id}`)
        tableData.value = tableData.value.filter(emp => emp.id !== id)
    } catch (err) {
        console.error('删除失败', err)
    }
}

// 翻页
const handlePageChange = (page: number) => {
    currentPage.value = page
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
