<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加供应商</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="supplier_id" label="供应商ID" width="100" />
            <el-table-column prop="supplier_name" label="供应商名称" />
            <el-table-column prop="contact_person" label="联系人姓名" />
            <el-table-column prop="contact_phone" label="联系电话" />
            <el-table-column prop="email" label="邮箱" />
            <el-table-column prop="status" label="状态" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.supplier_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 10px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="600px">
            <el-form :model="form" label-width="120px" :rules="rules" ref="formRef" status-icon>
                <el-form-item label="供应商名称" prop="supplier_name">
                    <el-input v-model="form.supplier_name" autocomplete="off" />
                </el-form-item>
                <el-form-item label="联系人姓名" prop="contact_person">
                    <el-input v-model="form.contact_person" autocomplete="off" />
                </el-form-item>
                <el-form-item label="联系电话" prop="contact_phone" required>
                    <el-input v-model="form.contact_phone" autocomplete="off" />
                </el-form-item>
                <el-form-item label="邮箱" prop="email">
                    <el-input v-model="form.email" autocomplete="off" />
                </el-form-item>
                <el-form-item label="状态" prop="status">
                    <el-select v-model="form.status" placeholder="请选择状态">
                        <el-option label="正常" value="正常" />
                        <el-option label="停用" value="停用" />
                        <el-option label="黑名单" value="黑名单" />
                    </el-select>
                </el-form-item>
                <el-form-item label="备注" prop="remark">
                    <el-input v-model="form.remark" type="textarea" autocomplete="off" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="submitForm">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import type { FormInstance } from 'element-plus'

interface SupplierInfo {
    supplier_id: number
    supplier_name: string
    contact_person: string
    contact_phone: string
    email?: string
    created_at?: string
    status?: string
    remark?: string
}

const generateFakeSuppliers = (): SupplierInfo[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        supplier_id: i + 1,
        supplier_name: `供应商-${i + 1}`,
        contact_person: `联系人-${i + 1}`,
        contact_phone: `138000000${i.toString().padStart(2, '0')}`,
        email: `supplier${i + 1}@example.com`,
        created_at: new Date().toISOString(),
        status: '正常',
        remark: `备注信息-${i + 1}`
    }))
}

const tableData = ref<SupplierInfo[]>(generateFakeSuppliers())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加供应商')
const form = ref<Partial<SupplierInfo>>({})

const formRef = ref<FormInstance>()

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SupplierInfo) => {
    dialogTitle.value = row ? '编辑供应商' : '添加供应商'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.supplier_id) {
        const index = tableData.value.findIndex(item => item.supplier_id === form.value.supplier_id)
        if (index !== -1) {
            tableData.value[index] = form.value as SupplierInfo
        }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SupplierInfo), supplier_id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (supplier_id: number) => {
    tableData.value = tableData.value.filter(item => item.supplier_id !== supplier_id)
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const rules = {
    supplier_name: [{ required: true, message: '供应商名称不能为空', trigger: 'blur' }],
    contact_person: [{ required: true, message: '联系人姓名不能为空', trigger: 'blur' }],
    contact_phone: [{ required: true, message: '联系电话不能为空', trigger: 'blur' }],
    email: [
        { type: 'email', message: '邮箱格式不正确', trigger: ['blur', 'change'], required: false }
    ],
    status: [{ required: true, message: '请选择状态', trigger: 'change' }]
}

const submitForm = () => {
    formRef.value?.validate(valid => {
        if (valid) {
            handleSave()
        }
    })
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
