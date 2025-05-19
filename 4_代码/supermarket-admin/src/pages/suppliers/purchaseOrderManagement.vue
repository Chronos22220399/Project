<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加采购订单</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="orderId" label="订单ID" width="110" />
            <el-table-column prop="supplierName" label="供应商名称" />
            <el-table-column prop="orderNumber" label="订单编号" />
            <el-table-column prop="orderDate" label="订单日期" width="130" />
            <el-table-column prop="totalAmount" label="总金额" width="120" />
            <el-table-column label="操作" width="160">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.orderId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 12px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="520px">
            <el-form :model="form" label-width="120px" ref="formRef">
                <el-form-item label="供应商名称" prop="supplierName"
                    :rules="[{ required: true, message: '请输入供应商名称', trigger: 'blur' }]">
                    <el-input v-model="form.supplierName" />
                </el-form-item>
                <el-form-item label="订单编号" prop="orderNumber"
                    :rules="[{ required: true, message: '请输入订单编号', trigger: 'blur' }]">
                    <el-input v-model="form.orderNumber" />
                </el-form-item>
                <el-form-item label="订单日期" prop="orderDate"
                    :rules="[{ required: true, message: '请选择订单日期', trigger: 'change' }]">
                    <el-date-picker v-model="form.orderDate" type="date" placeholder="选择订单日期" />
                </el-form-item>
                <el-form-item label="总金额" prop="totalAmount"
                    :rules="[{ required: true, type: 'number', message: '请输入总金额', trigger: 'blur' }]">
                    <el-input v-model.number="form.totalAmount" type="number" min="0" />
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
import type { Ref } from 'vue'

interface PurchaseOrder {
    orderId: number
    supplierName: string
    orderNumber: string
    orderDate: string
    totalAmount: number
}

const generateFakeOrders = (): PurchaseOrder[] => {
    return Array.from({ length: 25 }, (_, i) => ({
        orderId: i + 1,
        supplierName: `供应商-${(i % 10) + 1}`,
        orderNumber: `PO-${20240515 + i}`,
        orderDate: `2024-04-${((i % 30) + 1).toString().padStart(2, '0')}`,
        totalAmount: Number((Math.random() * 20000 + 1000).toFixed(2))
    }))
}

const tableData = ref < PurchaseOrder[] > (generateFakeOrders())
const currentPage = ref(1)
const pageSize = ref(8)
const dialogVisible = ref(false)
const dialogTitle = ref('添加采购订单')
const form = ref < Partial < PurchaseOrder >> ({})
const formRef = ref < InstanceType < typeof import('element-plus').ElForm > | null > (null)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: PurchaseOrder) => {
    dialogTitle.value = row ? '编辑采购订单' : '添加采购订单'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    formRef.value?.validate(valid => {
        if (!valid) return
        if (form.value.orderId) {
            const index = tableData.value.findIndex(item => item.orderId === form.value.orderId)
            if (index !== -1) {
                tableData.value[index] = form.value as PurchaseOrder
            }
        } else {
            const newId = Date.now()
            tableData.value.push({ ...(form.value as PurchaseOrder), orderId: newId })
        }
        dialogVisible.value = false
    })
}

const handleDelete = (orderId: number) => {
    tableData.value = tableData.value.filter(item => item.orderId !== orderId)
    if (paginatedData.value.length === 0 && currentPage.value > 1) {
        currentPage.value--
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 16px;
}
</style>
