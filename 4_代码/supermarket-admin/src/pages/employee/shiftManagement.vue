<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加排班</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="排班ID" width="80" />
            <el-table-column prop="employeeId" label="员工ID" width="100" />
            <el-table-column prop="employeeName" label="员工姓名" />
            <el-table-column prop="shift" label="班次" />
            <el-table-column prop="date" label="排班日期" />
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
                <el-form-item label="班次">
                    <el-select v-model="form.shift" placeholder="选择班次">
                        <el-option label="早班" value="早班" />
                        <el-option label="中班" value="中班" />
                        <el-option label="晚班" value="晚班" />
                    </el-select>
                </el-form-item>
                <el-form-item label="排班日期">
                    <el-date-picker v-model="form.date" type="date" placeholder="选择日期" />
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
import axios from 'axios'

interface Schedule {
    id: number
    employeeId: string
    employeeName: string
    shift: string
    date: string
}

// 假数据
const generateFakeSchedules = (): Schedule[] => {
    const names = ['张三', '李四', '王五', '赵六', '钱七']
    const shifts = ['早班', '中班', '晚班']
    const today = new Date()
    return Array.from({ length: 50 }, (_, i) => ({
        id: i + 1,
        employeeId: 'EMP' + (1000 + i),
        employeeName: names[i % names.length],
        shift: shifts[i % shifts.length],
        date: new Date(today.getTime() + i * 86400000).toISOString().split('T')[0]
    }))
}

const tableData = ref < Schedule[] > (generateFakeSchedules())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加排班')
const form = ref < Partial < Schedule >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: Schedule) => {
    dialogTitle.value = row ? '编辑排班' : '添加排班'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = async () => {
    const newData = { ...form.value }
    try {
        if (form.value.id) {
            await axios.put(`/api/schedule/${form.value.id}`, newData)
            const index = tableData.value.findIndex(item => item.id === form.value.id)
            if (index !== -1) tableData.value[index] = form.value as Schedule
        } else {
            const response = await axios.post('/api/schedule', newData)
            const newId = response.data.id || Date.now()
            tableData.value.push({ ...(form.value as Schedule), id: newId })
        }
        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/schedule/${id}`)
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
