<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加退货记录</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="return_id" label="退货ID" width="100" />
            <el-table-column prop="order_id" label="原订单ID" width="100" />
            <el-table-column prop="return_time" label="退货时间" width="180" />
            <el-table-column prop="cashier_id" label="收银员ID" width="100" />
            <el-table-column prop="member_id" label="会员ID" width="100" />
            <el-table-column prop="return_amount" label="退货金额" width="120" />
            <el-table-column prop="refund_method" label="退款方式" width="120" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="300">
                <template #default="scope">
                    <el-button size="small" @click="openDetail(scope.row.return_id)">查看明细</el-button>
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.return_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <!-- 添加/编辑退货记录弹窗 -->
        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="600px">
            <el-form :model="form" label-width="120px">
                <el-form-item label="原订单ID">
                    <el-input v-model.number="form.order_id" type="number" />
                </el-form-item>
                <el-form-item label="退货时间">
                    <el-date-picker v-model="form.return_time" type="datetime" placeholder="选择日期时间"
                        style="width: 100%" />
                </el-form-item>
                <el-form-item label="收银员ID">
                    <el-input v-model.number="form.cashier_id" type="number" />
                </el-form-item>
                <el-form-item label="会员ID">
                    <el-input v-model.number="form.member_id" type="number" />
                </el-form-item>
                <el-form-item label="退货金额">
                    <el-input v-model.number="form.return_amount" type="number" step="0.01" />
                </el-form-item>
                <el-form-item label="退款方式">
                    <el-select v-model="form.refund_method" placeholder="请选择退款方式">
                        <el-option label="原路退回" value="原路退回" />
                        <el-option label="现金" value="现金" />
                        <el-option label="其他" value="其他" />
                    </el-select>
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

        <!-- 退货明细弹窗组件 -->
        <ReturnDetailDialog ref="detailDialogRef" />
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import ReturnDetailDialog from './ReturnDetailDialog.vue'

interface SalesReturn {
    return_id: number
    order_id: number
    return_time: string
    cashier_id: number
    member_id: number | null
    return_amount: number
    refund_method: string
    remark: string | null
}

// 假数据生成
const tableData = ref<SalesReturn[]>(
    Array.from({ length: 25 }, (_, i) => ({
        return_id: i + 1,
        order_id: 1000 + i,
        return_time: '2025-05-20 14:30:00',
        cashier_id: 200 + (i % 5),
        member_id: i % 3 === 0 ? null : 5000 + i,
        return_amount: +(Math.random() * 500).toFixed(2),
        refund_method: ['原路退回', '现金', '其他'][i % 3],
        remark: i % 4 === 0 ? '客户退货' : null,
    }))
)

const pageSize = ref(10)
const currentPage = ref(1)
const dialogVisible = ref(false)
const dialogTitle = ref('添加退货记录')
const form = ref<Partial<SalesReturn>>({})
const detailDialogRef = ref()

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SalesReturn) => {
    dialogTitle.value = row ? '编辑退货记录' : '添加退货记录'
    form.value = row ? { ...row } : {
        return_time: new Date().toISOString().slice(0, 16).replace('T', ' '), // 默认当前时间（字符串格式）
        refund_method: '原路退回',
    }
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.return_id) {
        const idx = tableData.value.findIndex(item => item.return_id === form.value.return_id)
        if (idx !== -1) tableData.value[idx] = { ...(form.value as SalesReturn) }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SalesReturn), return_id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (return_id: number) => {
    tableData.value = tableData.value.filter(item => item.return_id !== return_id)
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

// 打开明细弹窗，生成假数据传入
const openDetail = (return_id: number) => {
    const details = generateFakeReturnItems(return_id)
    detailDialogRef.value.open(details)
}

// 假数据生成：退货明细表 SalesReturnItem
function generateFakeReturnItems(return_id: number) {
    const goods = [
        { id: 101, name: '苹果' },
        { id: 102, name: '牙膏' },
        { id: 103, name: '洗衣液' },
        { id: 104, name: '面包' },
        { id: 105, name: '牛奶' }
    ]

    return Array.from({ length: 3 + Math.floor(Math.random() * 3) }, (_, i) => {
        const product = goods[i % goods.length]
        const original_quantity = Math.floor(Math.random() * 10) + 1
        const return_quantity = Math.floor(Math.random() * original_quantity) + 1
        const unit_price = +(Math.random() * 50).toFixed(2)
        return {
            item_id: Date.now() + i,
            return_id,
            goods_id: product.id,
            product_name: product.name,
            original_quantity,
            return_quantity,
            refund_amount: +(unit_price * return_quantity).toFixed(2),
            unit_price
        }
    })
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
