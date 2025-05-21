<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加员工</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="employee_id" label="员工ID" width="100" />
            <el-table-column prop="employee_name" label="姓名" />
            <el-table-column prop="gender" label="性别" />
            <el-table-column prop="birth_date" label="出生日期" />
            <el-table-column prop="phone" label="电话" />
            <el-table-column prop="id_number" label="身份证号" />
            <el-table-column prop="hire_date" label="入职日期" />
            <el-table-column prop="position_name" label="岗位" />
            <el-table-column prop="status" label="状态" />
            <el-table-column prop="address" label="家庭住址" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.employee_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="姓名">
                    <el-input v-model="form.employee_name" />
                </el-form-item>

                <el-form-item label="性别">
                    <el-select v-model="form.gender" placeholder="选择性别">
                        <el-option label="男" value="男" />
                        <el-option label="女" value="女" />
                    </el-select>
                </el-form-item>

                <el-form-item label="出生日期">
                    <el-date-picker v-model="form.birth_date" type="date" placeholder="选择出生日期" />
                </el-form-item>

                <el-form-item label="电话">
                    <el-input v-model="form.phone" />
                </el-form-item>

                <el-form-item label="身份证号">
                    <el-input v-model="form.id_number" />
                </el-form-item>

                <el-form-item label="入职日期">
                    <el-date-picker v-model="form.hire_date" type="date" placeholder="选择入职日期" />
                </el-form-item>

                <el-form-item label="岗位">
                    <el-select v-model="form.position_id" placeholder="选择岗位">
                        <el-option v-for="pos in positions" :key="pos.position_id" :label="pos.position_name"
                            :value="pos.position_id" />
                    </el-select>
                </el-form-item>

                <el-form-item label="状态">
                    <el-select v-model="form.status" placeholder="选择状态">
                        <el-option label="在职" value="在职" />
                        <el-option label="离职" value="离职" />
                        <el-option label="休假" value="休假" />
                    </el-select>
                </el-form-item>

                <el-form-item label="家庭住址">
                    <el-input v-model="form.address" />
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

interface Position {
    position_id: number
    position_name: string
    department: string
    description: string
    base_salary: number
    is_manager: boolean
}

interface Employee {
    employee_id: number
    employee_name: string
    gender: string
    birth_date: string
    phone: string
    id_number: string
    hire_date: string
    position_id: number
    position_name?: string // 用于显示岗位名称
    status: string
    address: string
}

// 模拟岗位数据（真实项目可用接口获取）
const positions = ref<Position[]>([
    { position_id: 1, position_name: '销售经理', department: '销售部', description: '', base_salary: 8000, is_manager: true },
    { position_id: 2, position_name: '技术主管', department: '技术部', description: '', base_salary: 9000, is_manager: true },
    { position_id: 3, position_name: '财务职员', department: '财务部', description: '', base_salary: 6000, is_manager: false },
    { position_id: 4, position_name: '人事专员', department: '人事部', description: '', base_salary: 5500, is_manager: false },
])

// 生成假数据（包含岗位名称）
const generateFakeEmployees = (): Employee[] => {
    const genders = ['男', '女']
    const statuses = ['在职', '离职', '休假']
    return Array.from({ length: 50 }, (_, i) => {
        const pos = positions.value[Math.floor(Math.random() * positions.value.length)]
        return {
            employee_id: i + 1,
            employee_name: `员工${i + 1}`,
            gender: genders[Math.floor(Math.random() * genders.length)],
            birth_date: `1990-${String(Math.floor(Math.random() * 12) + 1).padStart(2, '0')}-${String(Math.floor(Math.random() * 28) + 1).padStart(2, '0')}`,
            phone: `13${Math.floor(Math.random() * 1000000000)}`,
            id_number: `320************${String(1000 + i).slice(-4)}`,
            hire_date: `2023-${String(Math.floor(Math.random() * 12) + 1).padStart(2, '0')}-${String(Math.floor(Math.random() * 28) + 1).padStart(2, '0')}`,
            position_id: pos.position_id,
            position_name: pos.position_name,
            status: statuses[Math.floor(Math.random() * statuses.length)],
            address: `北京市朝阳区XX街道${i + 1}号`,
        }
    })
}

const tableData = ref<Employee[]>(generateFakeEmployees())
const dialogVisible = ref(false)
const dialogTitle = ref('添加员工')
const form = ref<Partial<Employee>>({})

const currentPage = ref(1)
const pageSize = ref(10)
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: Employee) => {
    dialogTitle.value = row ? '编辑员工' : '添加员工'
    if (row) {
        form.value = { ...row }
    } else {
        form.value = {}
    }
    dialogVisible.value = true
}

const handleSave = async () => {
    const employeeData = { ...form.value }

    // 根据 position_id 填充 position_name，保持表格显示
    const pos = positions.value.find(p => p.position_id === employeeData.position_id)
    if (pos) {
        employeeData.position_name = pos.position_name
    }

    try {
        if (employeeData.employee_id) {
            // 编辑
            const index = tableData.value.findIndex(emp => emp.employee_id === employeeData.employee_id)
            if (index !== -1) {
                tableData.value[index] = employeeData as Employee
            }
            // 这里可以调用接口: await axios.put(`/api/employee/${employeeData.employee_id}`, employeeData)
        } else {
            // 新增
            employeeData.employee_id = Date.now() // 伪ID
            tableData.value.push(employeeData as Employee)
            // 这里可以调用接口: await axios.post('/api/employee', employeeData)
        }
        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

const handleDelete = async (id: number) => {
    try {
        tableData.value = tableData.value.filter(emp => emp.employee_id !== id)
        // 这里可以调用接口: await axios.delete(`/api/employee/${id}`)
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
