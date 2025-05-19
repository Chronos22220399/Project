<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加用户</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="userId" label="用户ID" width="100" />
            <el-table-column prop="username" label="用户名" />
            <el-table-column prop="password" label="密码" />
            <el-table-column prop="employeeId" label="员工ID" />
            <el-table-column prop="role" label="角色" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.userId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="用户名"><el-input v-model="form.username" /></el-form-item>
                <el-form-item label="密码"><el-input type="password" v-model="form.password" /></el-form-item>
                <el-form-item label="员工ID"><el-input v-model="form.employeeId" /></el-form-item>
                <el-form-item label="角色"><el-input v-model="form.role" /></el-form-item>
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

interface UserInfo {
    userId: number
    username: string
    password: string
    employeeId: number
    role: string
}

const generateFakeUsers = (): UserInfo[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        userId: i + 1,
        username: `user${i + 1}`,
        password: '******',
        employeeId: 1000 + i,
        role: i % 2 === 0 ? '管理员' : '普通用户'
    }))
}

const tableData = ref < UserInfo[] > (generateFakeUsers())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加用户')
const form = ref < Partial < UserInfo >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: UserInfo) => {
    dialogTitle.value = row ? '编辑用户' : '添加用户'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.userId) {
        const index = tableData.value.findIndex(item => item.userId === form.value.userId)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as UserInfo) }
        }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as UserInfo), userId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (userId: number) => {
    tableData.value = tableData.value.filter(item => item.userId !== userId)
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
