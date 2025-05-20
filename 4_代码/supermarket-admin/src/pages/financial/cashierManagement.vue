<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加收银记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="recordId" label="记录ID" width="100" />
            <el-table-column prop="cashierId" label="收银员ID" />
            <el-table-column prop="amount" label="金额" />
            <el-table-column prop="time" label="时间" />
            <el-table-column prop="paymentMethod" label="支付方式" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.recordId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="收银员ID"><el-input v-model="form.cashierId" /></el-form-item>
                <el-form-item label="金额"><el-input v-model="form.amount" /></el-form-item>
                <el-form-item label="时间"><el-date-picker v-model="form.time" type="datetime" /></el-form-item>
                <el-form-item label="支付方式"><el-input v-model="form.paymentMethod" /></el-form-item>
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

interface CashierRecord {
    recordId: number
    cashierId: number
    amount: number
    time: string
    paymentMethod: string
}

const generateFakeRecords = (): CashierRecord[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        recordId: i + 1,
        cashierId: 1000 + i,
        amount: (Math.random() * 500).toFixed(2),
        time: '2025-05-15 10:00:00',
        paymentMethod: i % 2 === 0 ? '现金' : '支付宝'
    })).map(item => ({ ...item, amount: Number(item.amount) }))
}

const tableData = ref < CashierRecord[] > (generateFakeRecords())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加收银记录')
const form = ref < Partial < CashierRecord >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: CashierRecord) => {
    dialogTitle.value = row ? '编辑收银记录' : '添加收银记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.recordId) {
        const index = tableData.value.findIndex(item => item.recordId === form.value.recordId)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as CashierRecord) }
        }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as CashierRecord), recordId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (recordId: number) => {
    tableData.value = tableData.value.filter(item => item.recordId !== recordId)
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
