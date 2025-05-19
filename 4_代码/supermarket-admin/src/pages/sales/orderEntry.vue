<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加订单</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="orderId" label="订单ID" width="100" />
            <el-table-column prop="customerName" label="客户姓名" />
            <el-table-column prop="totalAmount" label="总金额" />
            <el-table-column prop="orderDate" label="下单日期" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.orderId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />
        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="客户姓名"><el-input v-model="form.customerName" /></el-form-item>
                <el-form-item label="总金额"><el-input v-model="form.totalAmount" /></el-form-item>
                <el-form-item label="下单日期"><el-date-picker v-model="form.orderDate" type="date" /></el-form-item>
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

interface SalesOrder {
    orderId: number
    customerName: string
    totalAmount: number
    orderDate: string
}

const tableData = ref<SalesOrder[]>(Array.from({ length: 20 }, (_, i) => ({
    orderId: i + 1,
    customerName: `客户${i + 1}`,
    totalAmount: 100 + i * 10,
    orderDate: '2025-05-01'
})))

const pageSize = ref(10)
const currentPage = ref(1)
const dialogVisible = ref(false)
const dialogTitle = ref('添加订单')
const form = ref<Partial<SalesOrder>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SalesOrder) => {
    dialogTitle.value = row ? '编辑订单' : '添加订单'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.orderId) {
        const index = tableData.value.findIndex(item => item.orderId === form.value.orderId)
        if (index !== -1) tableData.value[index] = { ...(form.value as SalesOrder) }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SalesOrder), orderId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (orderId: number) => {
    tableData.value = tableData.value.filter(item => item.orderId !== orderId)
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
