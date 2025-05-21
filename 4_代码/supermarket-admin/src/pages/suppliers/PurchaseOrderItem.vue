<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加采购订单明细</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="item_id" label="明细ID" width="100" />
            <el-table-column prop="purchase_order_id" label="采购订单ID" width="140" />
            <el-table-column prop="goods_id" label="商品ID" width="100" />
            <el-table-column prop="unit_id" label="单位ID" width="100" />
            <el-table-column prop="unit_price" label="单价" width="100" />
            <el-table-column prop="quantity" label="采购数量" width="120" />
            <el-table-column prop="subtotal" label="小计金额" width="120" />
            <el-table-column label="操作" width="160">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.item_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 12px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="520px">
            <el-form :model="form" ref="formRef" label-width="120px" :rules="rules">
                <el-form-item label="采购订单ID" prop="purchase_order_id" required>
                    <el-input v-model.number="form.purchase_order_id" type="number" min="1" />
                </el-form-item>
                <el-form-item label="商品ID" prop="goods_id" required>
                    <el-input v-model.number="form.goods_id" type="number" min="1" />
                </el-form-item>
                <el-form-item label="单位ID" prop="unit_id" required>
                    <el-input v-model.number="form.unit_id" type="number" min="1" />
                </el-form-item>
                <el-form-item label="单价" prop="unit_price" required>
                    <el-input v-model.number="form.unit_price" type="number" min="0" step="0.01" />
                </el-form-item>
                <el-form-item label="采购数量" prop="quantity" required>
                    <el-input v-model.number="form.quantity" type="number" min="1" />
                </el-form-item>
                <el-form-item label="小计金额" prop="subtotal" required>
                    <el-input v-model.number="form.subtotal" type="number" min="0" step="0.01" :disabled="true" />
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
import { ref, computed, watch } from 'vue'
import type { Ref } from 'vue'

interface PurchaseOrderItem {
    item_id: number
    purchase_order_id: number
    goods_id: number
    unit_id: number
    unit_price: number
    quantity: number
    subtotal: number
}

// 模拟数据生成
const generateFakeItems = (): PurchaseOrderItem[] => {
    return Array.from({ length: 25 }, (_, i) => {
        const unitPrice = Number((Math.random() * 100 + 1).toFixed(2))
        const quantity = Math.floor(Math.random() * 10 + 1)
        return {
            item_id: i + 1,
            purchase_order_id: Math.floor(Math.random() * 10 + 1),
            goods_id: Math.floor(Math.random() * 50 + 1),
            unit_id: Math.floor(Math.random() * 5 + 1),
            unit_price: unitPrice,
            quantity,
            subtotal: Number((unitPrice * quantity).toFixed(2))
        }
    })
}

const tableData = ref<PurchaseOrderItem[]>(generateFakeItems())
const currentPage = ref(1)
const pageSize = ref(8)
const dialogVisible = ref(false)
const dialogTitle = ref('添加采购订单明细')
const form = ref<Partial<PurchaseOrderItem>>({})
const formRef = ref<InstanceType<typeof import('element-plus').ElForm> | null>(null)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const rules = {
    purchase_order_id: [{ required: true, type: 'number', message: '请输入采购订单ID', trigger: 'blur' }],
    goods_id: [{ required: true, type: 'number', message: '请输入商品ID', trigger: 'blur' }],
    unit_id: [{ required: true, type: 'number', message: '请输入单位ID', trigger: 'blur' }],
    unit_price: [{ required: true, type: 'number', message: '请输入单价', trigger: 'blur' }],
    quantity: [{ required: true, type: 'number', message: '请输入采购数量', trigger: 'blur' }],
    subtotal: [{ required: true, type: 'number', message: '请输入小计金额', trigger: 'blur' }],
}

// 打开弹窗（新增或编辑）
const openDialog = (row?: PurchaseOrderItem) => {
    dialogTitle.value = row ? '编辑采购订单明细' : '添加采购订单明细'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

// 监听单价和数量自动计算小计金额
watch(
    () => [form.value.unit_price, form.value.quantity],
    ([unit_price, quantity]) => {
        if (unit_price != null && quantity != null) {
            form.value.subtotal = Number((unit_price * quantity).toFixed(2))
        } else {
            form.value.subtotal = 0
        }
    }
)

const handleSave = () => {
    formRef.value?.validate((valid) => {
        if (!valid) return
        if (form.value.item_id) {
            // 编辑
            const index = tableData.value.findIndex(item => item.item_id === form.value.item_id)
            if (index !== -1) {
                tableData.value[index] = form.value as PurchaseOrderItem
            }
        } else {
            // 新增
            const newId = Date.now()
            tableData.value.push({ ...(form.value as PurchaseOrderItem), item_id: newId })
        }
        dialogVisible.value = false
    })
}

const handleDelete = (item_id: number) => {
    tableData.value = tableData.value.filter(item => item.item_id !== item_id)
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
