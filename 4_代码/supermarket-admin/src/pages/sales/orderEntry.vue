<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加订单</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="order_id" label="订单ID" width="100" />
            <el-table-column prop="sale_time" label="销售时间" width="180" />
            <el-table-column prop="cashier_id" label="收银员ID" width="100" />
            <el-table-column prop="member_id" label="会员ID" width="100" />
            <el-table-column prop="total_amount" label="总金额" width="120" />
            <el-table-column prop="paid_amount" label="支付金额" width="120" />
            <el-table-column prop="payment_method" label="支付方式" width="120" />
            <el-table-column prop="discount_info" label="折扣说明" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="280">
                <template #default="scope">
                    <el-button size="small" @click="openDetail(scope.row.order_id)">查看明细</el-button>
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.order_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <!-- 添加/编辑订单弹窗 -->
        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="600px">
            <el-form :model="form" label-width="120px">
                <el-form-item label="销售时间">
                    <el-date-picker v-model="form.sale_time" type="datetime" style="width: 100%" />
                </el-form-item>
                <el-form-item label="收银员ID">
                    <el-input v-model.number="form.cashier_id" type="number" />
                </el-form-item>
                <el-form-item label="会员ID">
                    <el-input v-model.number="form.member_id" type="number" />
                </el-form-item>
                <el-form-item label="总金额">
                    <el-input-number v-model="form.total_amount" :step="0.01" style="width: 100%" />
                </el-form-item>
                <el-form-item label="支付金额">
                    <el-input-number v-model="form.paid_amount" :step="0.01" style="width: 100%" />
                </el-form-item>
                <el-form-item label="支付方式">
                    <el-select v-model="form.payment_method" placeholder="请选择支付方式">
                        <el-option label="现金" value="现金" />
                        <el-option label="微信" value="微信" />
                        <el-option label="支付宝" value="支付宝" />
                        <el-option label="银行卡" value="银行卡" />
                    </el-select>
                </el-form-item>
                <el-form-item label="折扣说明">
                    <el-input v-model="form.discount_info" />
                </el-form-item>
                <el-form-item label="备注">
                    <el-input v-model="form.remark" type="textarea" />
                </el-form-item>
            </el-form>

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSave">保存</el-button>
            </template>
        </el-dialog>

        <!-- 订单明细弹窗组件 -->
        <OrderDetailDialog ref="detailDialogRef" />
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import OrderDetailDialog from './OrderDetailDialog.vue'

interface SalesOrder {
    order_id: number
    sale_time: string | Date
    cashier_id: number
    member_id: number | null
    total_amount: number
    paid_amount: number
    payment_method: string
    discount_info?: string | null
    remark?: string | null
}

interface OrderDetail {
    detail_id: number
    order_id: number
    product_name: string
    quantity: number
    price: number
}

// 假订单数据
const tableData = ref<SalesOrder[]>(
    Array.from({ length: 25 }, (_, i) => ({
        order_id: i + 1,
        sale_time: new Date().toISOString(),
        cashier_id: 200 + (i % 5),
        member_id: i % 3 === 0 ? null : 5000 + i,
        total_amount: +(1000 + Math.random() * 1000).toFixed(2),
        paid_amount: +(900 + Math.random() * 900).toFixed(2),
        payment_method: ['现金', '微信', '支付宝', '银行卡'][i % 4],
        discount_info: i % 4 === 0 ? '满100减10' : null,
        remark: i % 5 === 0 ? '大客户订单' : null,
    }))
)

// 假订单明细数据，key是order_id
const orderDetailsMap = ref<Record<number, OrderDetail[]>>({
    1: [
        { detail_id: 1, order_id: 1, product_name: '苹果', quantity: 3, price: 3.5 },
        { detail_id: 2, order_id: 1, product_name: '香蕉', quantity: 2, price: 2.0 },
    ],
    2: [
        { detail_id: 3, order_id: 2, product_name: '橙子', quantity: 5, price: 4.5 },
    ],
    // 你可以继续补充其它订单明细
})

const pageSize = ref(10)
const currentPage = ref(1)
const dialogVisible = ref(false)
const dialogTitle = ref('添加订单')
const form = ref<Partial<SalesOrder>>({})
const detailDialogRef = ref<any>()

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SalesOrder) => {
    dialogTitle.value = row ? '编辑订单' : '添加订单'
    form.value = row
        ? { ...row }
        : {
            sale_time: new Date(),
            payment_method: '现金',
        }
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.order_id) {
        const index = tableData.value.findIndex(item => item.order_id === form.value.order_id)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as SalesOrder) }
        }
    } else {
        const newOrder: SalesOrder = {
            ...(form.value as SalesOrder),
            order_id: Date.now(),
        }
        tableData.value.unshift(newOrder)
    }
    dialogVisible.value = false
}

const handleDelete = (order_id: number) => {
    tableData.value = tableData.value.filter(item => item.order_id !== order_id)
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const openDetail = (order_id: number) => {
    const details = orderDetailsMap.value[order_id] || []
    detailDialogRef.value.open(details)
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
