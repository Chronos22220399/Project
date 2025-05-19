<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加供应商</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="supplierId" label="供应商ID" width="100" />
            <el-table-column prop="name" label="供应商名称" />
            <el-table-column prop="contactPerson" label="联系人" />
            <el-table-column prop="phone" label="联系电话" />
            <el-table-column prop="address" label="地址" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.supplierId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 10px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="100px">
                <el-form-item label="供应商名称">
                    <el-input v-model="form.name" />
                </el-form-item>
                <el-form-item label="联系人">
                    <el-input v-model="form.contactPerson" />
                </el-form-item>
                <el-form-item label="联系电话">
                    <el-input v-model="form.phone" />
                </el-form-item>
                <el-form-item label="地址">
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

interface SupplierInfo {
    supplierId: number
    name: string
    contactPerson: string
    phone: string
    address: string
}

const generateFakeSuppliers = (): SupplierInfo[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        supplierId: i + 1,
        name: `供应商-${i + 1}`,
        contactPerson: `联系人-${i + 1}`,
        phone: `138000000${i.toString().padStart(2, '0')}`,
        address: `地址-${i + 1}`
    }))
}

const tableData = ref < SupplierInfo[] > (generateFakeSuppliers())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加供应商')
const form = ref < Partial < SupplierInfo >> ({})

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
    if (form.value.supplierId) {
        const index = tableData.value.findIndex(item => item.supplierId === form.value.supplierId)
        if (index !== -1) {
            tableData.value[index] = form.value as SupplierInfo
        }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SupplierInfo), supplierId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (supplierId: number) => {
    tableData.value = tableData.value.filter(item => item.supplierId !== supplierId)
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
