<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加考勤记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="考勤ID" width="80" />
            <el-table-column prop="employeeId" label="员工ID" width="100" />
            <el-table-column prop="employeeName" label="员工姓名" />
            <el-table-column prop="date" label="考勤日期" />
            <el-table-column prop="status" label="考勤状态" />
            <el-table-column prop="checkInTime" label="签到时间" />
            <el-table-column prop="checkOutTime" label="签退时间" />
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
                <el-form-item label="考勤日期">
                    <el-date-picker v-model="form.date" type="date" placeholder="选择日期" />
                </el-form-item>
                <el-form-item label="考勤状态">
                    <el-select v-model="form.status" placeholder="选择状态">
                        <el-option label="正常" value="正常" />
                        <el-option label="迟到" value="迟到" />
                        <el-option label="早退" value="早退" />
                        <el-option label="缺勤" value="缺勤" />
                        <el-option label="请假" value="请假" />
                    </el-select>
                </el-form-item>
                <el-form-item label="签到时间"><el-time-picker v-model="form.checkInTime"
                        placeholder="选择时间" /></el-form-item>
                <el-form-item label="签退时间"><el-time-picker v-model="form.checkOutTime"
                        placeholder="选择时间" /></el-form-item>
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

interface Attendance {
    id: number
    employeeId: string
    employeeName: string
    date: string
    status: string
    checkInTime: string
    checkOutTime: string
}

// 假数据生成
const generateFakeAttendance = (): Attendance[] => {
    const names = ['张三', '李四', '王五', '赵六', '钱七']
    const statuses = ['正常', '迟到', '早退', '缺勤', '请假']
    return Array.from({ length: 50 }, (_, i) => {
        const date = new Date()
        date.setDate(date.getDate() - i)
        return {
            id: i + 1,
            employeeId: 'EMP' + (1000 + i),
            employeeName: names[i % names.length],
            date: date.toISOString().split('T')[0],
            status: statuses[i % statuses.length],
            checkInTime: '09:00',
            checkOutTime: '18:00',
        }
    })
}

const tableData = ref < Attendance[] > (generateFakeAttendance())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加考勤记录')
const form = ref < Partial < Attendance >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: Attendance) => {
    dialogTitle.value = row ? '编辑考勤记录' : '添加考勤记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = async () => {
    const newData = { ...form.value }
    try {
        if (form.value.id) {
            await axios.put(`/api/attendance/${form.value.id}`, newData)
            const index = tableData.value.findIndex(item => item.id === form.value.id)
            if (index !== -1) tableData.value[index] = form.value as Attendance
        } else {
            const response = await axios.post('/api/attendance', newData)
            const newId = response.data.id || Date.now()
            tableData.value.push({ ...(form.value as Attendance), id: newId })
        }
        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/attendance/${id}`)
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
