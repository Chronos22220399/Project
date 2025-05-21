<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加用户</el-button>
            <el-button type="success" @click="showRoleDialog = true" style="margin-left: 8px">角色权限管理</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="user_id" label="用户ID" width="100" />
            <el-table-column prop="username" label="用户名" />
            <el-table-column prop="employee_id" label="员工ID" />
            <el-table-column label="角色">
                <template #default="scope">{{ getRoleName(scope.row.role_id) }}</template>
            </el-table-column>
            <el-table-column prop="status" label="状态" />
            <el-table-column prop="created_at" label="创建时间" />
            <el-table-column prop="last_login_at" label="最后登录时间" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.user_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="100px">
                <el-form-item label="用户名">
                    <el-input v-model="form.username" autocomplete="off" />
                </el-form-item>
                <el-form-item label="密码">
                    <el-input type="password" v-model="form.password" autocomplete="new-password"
                        placeholder="不修改请留空" />
                </el-form-item>
                <el-form-item label="员工ID">
                    <el-input v-model.number="form.employee_id" type="number" autocomplete="off" />
                </el-form-item>
                <el-form-item label="角色">
                    <el-select v-model="form.role_id" placeholder="请选择角色" style="width: 100%">
                        <el-option v-for="role in roles" :key="role.role_id" :label="role.role_name"
                            :value="role.role_id" />
                    </el-select>
                </el-form-item>
                <el-form-item label="状态">
                    <el-select v-model="form.status" placeholder="请选择状态" style="width: 100%">
                        <el-option label="启用" value="enabled" />
                        <el-option label="停用" value="disabled" />
                        <el-option label="锁定" value="locked" />
                    </el-select>
                </el-form-item>
                <el-form-item label="创建时间" v-if="form.created_at">
                    <el-input :model-value="form.created_at" disabled />
                </el-form-item>
                <el-form-item label="最后登录" v-if="form.last_login_at">
                    <el-input :model-value="form.last_login_at" disabled />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSave">保存</el-button>
            </template>
        </el-dialog>

        <!-- 角色权限管理弹窗 -->
        <el-dialog title="角色权限管理" v-model="showRoleDialog" width="700px" :destroy-on-close="true">
            <RoleManagement />
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from "vue"
import RoleManagement from "./RoleManagement.vue"

interface Role {
    role_id: number
    role_name: string
    description: string
    created_at: string
}

interface UserInfo {
    user_id: number
    username: string
    password_hash?: string
    employee_id: number
    role_id: number
    status: "enabled" | "disabled" | "locked"
    created_at?: string
    last_login_at?: string
    password?: string
}

const roles = ref<Role[]>([
    { role_id: 1, role_name: "管理员", description: "系统管理员", created_at: "2023-01-01" },
    { role_id: 2, role_name: "普通用户", description: "普通用户", created_at: "2023-01-01" }
])

const generateFakeUsers = (): UserInfo[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        user_id: i + 1,
        username: `user${i + 1}`,
        password_hash: "******",
        employee_id: 1000 + i,
        role_id: i % 2 === 0 ? 1 : 2,
        status: i % 3 === 0 ? "enabled" : i % 3 === 1 ? "disabled" : "locked",
        created_at: `2023-05-${(i % 30) + 1} 10:00:00`,
        last_login_at: `2023-05-${(i % 30) + 2} 08:30:00`
    }))
}

const tableData = ref<UserInfo[]>(generateFakeUsers())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref("添加用户")
const form = ref<Partial<UserInfo>>({})
const showRoleDialog = ref(false)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const getRoleName = (role_id: number) => {
    const role = roles.value.find((r) => r.role_id === role_id)
    return role ? role.role_name : ""
}

const openDialog = (row?: UserInfo) => {
    dialogTitle.value = row ? "编辑用户" : "添加用户"
    form.value = row ? { ...row, password: "" } : { status: "enabled" }
    dialogVisible.value = true
}

const handleSave = () => {
    if (!form.value.username) {
        alert("用户名不能为空")
        return
    }
    if (form.value.user_id) {
        const index = tableData.value.findIndex((u) => u.user_id === form.value.user_id)
        if (index !== -1) {
            if (form.value.password && form.value.password.trim() !== "") {
                form.value.password_hash = "******"
            }
            tableData.value[index] = { ...(form.value as UserInfo) }
        }
    } else {
        const newId = Date.now()
        if (form.value.password && form.value.password.trim() !== "") {
            form.value.password_hash = "******"
        } else {
            alert("新用户密码不能为空")
            return
        }
        tableData.value.push({
            ...(form.value as UserInfo),
            user_id: newId,
            created_at: new Date().toISOString(),
            last_login_at: ""
        })
    }
    dialogVisible.value = false
}

const handleDelete = (userId: number) => {
    tableData.value = tableData.value.filter((item) => item.user_id !== userId)
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
