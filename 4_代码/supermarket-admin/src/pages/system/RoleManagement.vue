<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加角色</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="role_id" label="角色ID" width="100" />
            <el-table-column prop="role_name" label="角色名称" />
            <el-table-column prop="description" label="角色描述" />
            <el-table-column prop="created_at" label="创建时间" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.role_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="100px">
                <el-form-item label="角色名称">
                    <el-input v-model="form.role_name" autocomplete="off" />
                </el-form-item>
                <el-form-item label="角色描述">
                    <el-input type="textarea" v-model="form.description" autocomplete="off" />
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
import { ref, computed } from "vue"

interface Role {
    role_id: number
    role_name: string
    description: string
    created_at: string
}

const tableData = ref<Role[]>([
    { role_id: 1, role_name: "管理员", description: "系统管理员", created_at: "2023-01-01" },
    { role_id: 2, role_name: "普通用户", description: "普通用户", created_at: "2023-01-01" }
])

const currentPage = ref(1)
const pageSize = ref(5)
const dialogVisible = ref(false)
const dialogTitle = ref("添加角色")
const form = ref<Partial<Role>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: Role) => {
    dialogTitle.value = row ? "编辑角色" : "添加角色"
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (!form.value.role_name) {
        alert("角色名称不能为空")
        return
    }
    if (form.value.role_id) {
        const index = tableData.value.findIndex(r => r.role_id === form.value.role_id)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as Role) }
        }
    } else {
        const newId = Date.now()
        tableData.value.push({
            ...(form.value as Role),
            role_id: newId,
            created_at: new Date().toISOString()
        })
    }
    dialogVisible.value = false
}

const handleDelete = (roleId: number) => {
    tableData.value = tableData.value.filter(r => r.role_id !== roleId)
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
