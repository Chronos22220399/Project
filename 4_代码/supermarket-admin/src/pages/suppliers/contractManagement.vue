<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加合同</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="contractId" label="合同ID" width="100" />
            <el-table-column prop="supplierName" label="供应商名称" />
            <el-table-column prop="contractNumber" label="合同编号" />
            <el-table-column prop="startDate" label="起始日期" />
            <el-table-column prop="endDate" label="结束日期" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.contractId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 10px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="120px">
                <el-form-item label="供应商名称">
                    <el-input v-model="form.supplierName" />
                </el-form-item>
                <el-form-item label="合同编号">
                    <el-input v-model="form.contractNumber" />
                </el-form-item>
                <el-form-item label="起始日期">
                    <el-date-picker v-model="form.startDate" type="date" placeholder="选择起始日期" />
                </el-form-item>
                <el-form-item label="结束日期">
                    <el-date-picker v-model="form.endDate" type="date" placeholder="选择结束日期" />
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

interface SupplierContract {
    contractId: number
    supplierName: string
    contractNumber: string
    startDate: string
    endDate: string
}

const generateFakeContracts = (): SupplierContract[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        contractId: i + 1,
        supplierName: `供应商-${(i % 10) + 1}`,
        contractNumber: `HT2024-${1000 + i}`,
        startDate: `2024-01-${(i % 28 + 1).toString().padStart(2, '0')}`,
        endDate: `2025-01-${(i % 28 + 1).toString().padStart(2, '0')}`
    }))
}

const tableData = ref < SupplierContract[] > (generateFakeContracts())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加合同')
const form = ref < Partial < SupplierContract >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SupplierContract) => {
    dialogTitle.value = row ? '编辑合同' : '添加合同'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.contractId) {
        const index = tableData.value.findIndex(item => item.contractId === form.value.contractId)
        if (index !== -1) {
            tableData.value[index] = form.value as SupplierContract
        }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SupplierContract), contractId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (contractId: number) => {
    tableData.value = tableData.value.filter(item => item.contractId !== contractId)
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
