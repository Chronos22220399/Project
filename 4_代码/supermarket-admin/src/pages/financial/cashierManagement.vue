<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加收银记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="cashier_record_id" label="记录ID" width="100" />
            <el-table-column prop="order_id" label="销售订单ID" />
            <el-table-column prop="cashier_id" label="收银员ID" />
            <el-table-column prop="payment_method" label="支付方式" />
            <el-table-column prop="receivable_amount" label="应收金额" />
            <el-table-column prop="paid_amount" label="实收金额" />
            <el-table-column prop="change_mount" label="找零金额" />
            <el-table-column prop="cashier_time" label="收银时间" />
            <el-table-column prop="counter_number" label="收银台编号" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger"
                        @click="handleDelete(scope.row.cashier_record_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="销售订单ID"><el-input v-model="form.order_id" /></el-form-item>
                <el-form-item label="收银员ID"><el-input v-model="form.cashier_id" /></el-form-item>
                <el-form-item label="支付方式"><el-input v-model="form.payment_method" /></el-form-item>
                <el-form-item label="应收金额"><el-input v-model="form.receivable_amount" /></el-form-item>
                <el-form-item label="实收金额"><el-input v-model="form.paid_amount" /></el-form-item>
                <el-form-item label="找零金额"><el-input v-model="form.change_mount" /></el-form-item>
                <el-form-item label="收银时间">
                    <el-date-picker v-model="form.cashier_time" type="datetime" value-format="YYYY-MM-DD HH:mm:ss" />
                </el-form-item>
                <el-form-item label="收银台编号"><el-input v-model="form.counter_number" /></el-form-item>
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
    cashier_record_id: number
    order_id: number
    cashier_id: number
    payment_method: string
    receivable_amount: number
    paid_amount: number
    change_mount: number
    cashier_time: string
    counter_number: string
}

// 模拟数据生成
const generateFakeRecords = (): CashierRecord[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        cashier_record_id: i + 1,
        order_id: 1000 + i,
        cashier_id: 2000 + i,
        payment_method: i % 2 === 0 ? '微信' : '支付宝',
        receivable_amount: 100 + i * 5,
        paid_amount: 100 + i * 5,
        change_mount: 0,
        cashier_time: '2025-05-15 10:00:00',
        counter_number: `A-${i + 1}`
    }))
}

const tableData = ref<CashierRecord[]>(generateFakeRecords())
const currentPage = ref(1)
const pageSize = ref(10)

const dialogVisible = ref(false)
const dialogTitle = ref('添加收银记录')
const form = ref<Partial<CashierRecord>>({})

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
    if (form.value.cashier_record_id) {
        const index = tableData.value.findIndex(item => item.cashier_record_id === form.value.cashier_record_id)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as CashierRecord) }
        }
    } else {
        const newId = Date.now()
        tableData.value.push({
            ...(form.value as CashierRecord),
            cashier_record_id: newId
        })
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.cashier_record_id !== id)
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
