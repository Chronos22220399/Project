<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加考勤记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="attendance_id" label="考勤ID" width="100" />
            <el-table-column prop="employee_id" label="员工ID" width="120" />
            <el-table-column prop="date" label="考勤日期" />
            <el-table-column prop="status" label="考勤状态" />
            <el-table-column prop="clock_in_time" label="上班打卡时间" />
            <el-table-column prop="clock_out_time" label="下班打卡时间" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.attendance_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="120px">
                <el-form-item label="员工ID">
                    <el-input v-model="form.employee_id" />
                </el-form-item>
                <el-form-item label="考勤日期">
                    <el-date-picker v-model="form.date" type="date" placeholder="选择日期" value-format="yyyy-MM-dd" />
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
                <el-form-item label="上班打卡时间">
                    <el-time-picker v-model="form.clock_in_time" placeholder="选择时间" format="HH:mm"
                        value-format="HH:mm" />
                </el-form-item>
                <el-form-item label="下班打卡时间">
                    <el-time-picker v-model="form.clock_out_time" placeholder="选择时间" format="HH:mm"
                        value-format="HH:mm" />
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

interface AttendanceRecord {
    attendance_id: number
    employee_id: string
    date: string
    status: string
    clock_in_time: string
    clock_out_time: string
}

const generateFakeData = (): AttendanceRecord[] => {
    const statuses = ['正常', '迟到', '早退', '缺勤', '请假']
    return Array.from({ length: 50 }, (_, i) => {
        const date = new Date()
        date.setDate(date.getDate() - i)
        return {
            attendance_id: i + 1,
            employee_id: 'EMP' + (1000 + i),
            date: date.toISOString().split('T')[0],
            status: statuses[i % statuses.length],
            clock_in_time: '09:00',
            clock_out_time: '18:00',
        }
    })
}

const tableData = ref<AttendanceRecord[]>(generateFakeData())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加考勤记录')
const form = ref<Partial<AttendanceRecord>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: AttendanceRecord) => {
    dialogTitle.value = row ? '编辑考勤记录' : '添加考勤记录'
    form.value = row ? { ...row } : {
        employee_id: '',
        date: '',
        status: '',
        clock_in_time: '',
        clock_out_time: ''
    }
    dialogVisible.value = true
}

const handleSave = async () => {
    if (!form.value.employee_id || !form.value.date) {
        alert('员工ID和考勤日期为必填项')
        return
    }
    const newData = { ...form.value } as AttendanceRecord
    try {
        if (newData.attendance_id) {
            await axios.put(`/api/attendance/${newData.attendance_id}`, newData)
            const index = tableData.value.findIndex(item => item.attendance_id === newData.attendance_id)
            if (index !== -1) tableData.value[index] = newData
        } else {
            const response = await axios.post('/api/attendance', newData)
            const newId = response.data?.attendance_id || Date.now()
            tableData.value.push({ ...newData, attendance_id: newId })
        }
        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/attendance/${id}`)
        tableData.value = tableData.value.filter(item => item.attendance_id !== id)
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
