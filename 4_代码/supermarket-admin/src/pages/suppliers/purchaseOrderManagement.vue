<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加采购订单</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="purchase_order_id" label="采购订单ID" width="130" />
            <el-table-column prop="supplierName" label="供应商名称" />
            <el-table-column prop="created_at" label="创建时间" width="160" />
            <el-table-column prop="created_by" label="创建人ID" width="120" />
            <el-table-column prop="expected_arrival_date" label="预计到货时间" width="160" />
            <el-table-column prop="actual_arrival_date" label="实际到货时间" width="160" />
            <el-table-column prop="total_amount" label="总金额" width="120" />
            <el-table-column prop="status" label="订单状态" width="120" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="160">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger"
                        @click="handleDelete(scope.row.purchase_order_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 12px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="700px">
            <el-form :model="form" label-width="140px" ref="formRef" :rules="rules">
                <el-form-item label="供应商" prop="supplier_id">
                    <el-select v-model="form.supplier_id" placeholder="请选择供应商">
                        <el-option v-for="supplier in suppliers" :key="supplier.id" :label="supplier.name"
                            :value="supplier.id" />
                    </el-select>
                </el-form-item>

                <el-form-item label="创建时间" prop="created_at">
                    <el-date-picker v-model="form.created_at" type="datetime" placeholder="选择创建时间"
                        style="width: 100%" />
                </el-form-item>

                <el-form-item label="创建人ID" prop="created_by">
                    <el-input v-model.number="form.created_by" type="number" min="1" placeholder="请输入创建人ID" />
                </el-form-item>

                <el-form-item label="预计到货时间" prop="expected_arrival_date">
                    <el-date-picker v-model="form.expected_arrival_date" type="date" placeholder="选择预计到货时间"
                        style="width: 100%" />
                </el-form-item>

                <el-form-item label="实际到货时间" prop="actual_arrival_date">
                    <el-date-picker v-model="form.actual_arrival_date" type="date" placeholder="选择实际到货时间"
                        style="width: 100%" />
                </el-form-item>

                <el-form-item label="总金额" prop="total_amount">
                    <el-input v-model.number="form.total_amount" type="number" min="0" placeholder="请输入总金额" />
                </el-form-item>

                <el-form-item label="订单状态" prop="status">
                    <el-select v-model="form.status" placeholder="请选择订单状态">
                        <el-option label="待审" value="待审" />
                        <el-option label="已下单" value="已下单" />
                        <el-option label="已入库" value="已入库" />
                        <el-option label="已取消" value="已取消" />
                    </el-select>
                </el-form-item>

                <el-form-item label="备注" prop="remark">
                    <el-input v-model="form.remark" type="textarea" placeholder="请输入备注" />
                </el-form-item>
            </el-form>

            <!-- ✅ 嵌入采购订单明细子组件 -->
            <div v-if="form.purchase_order_id" style="margin-top: 20px">
                <h4>采购订单明细</h4>
                <purchase-order-item-table :purchaseOrderId="form.purchase_order_id" />
            </div>

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSave">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import PurchaseOrderItemTable from './PurchaseOrderItem.vue'

interface PurchaseOrder {
    purchase_order_id: number
    supplier_id: number
    created_at: string
    created_by: number
    expected_arrival_date: string
    actual_arrival_date?: string
    total_amount: number
    status: string
    remark?: string
}

interface Supplier {
    id: number
    name: string
}

const suppliers: Supplier[] = Array.from({ length: 10 }, (_, i) => ({
    id: i + 1,
    name: `供应商-${i + 1}`,
}))

const generateFakeOrders = (): PurchaseOrder[] => {
    return Array.from({ length: 25 }, (_, i) => ({
        purchase_order_id: i + 1,
        supplier_id: (i % 10) + 1,
        created_at: `2024-04-${((i % 30) + 1).toString().padStart(2, '0')} 10:00:00`,
        created_by: (i % 5) + 1,
        expected_arrival_date: `2024-05-${((i % 30) + 1).toString().padStart(2, '0')}`,
        actual_arrival_date: i % 2 === 0 ? `2024-05-${((i % 30) + 1).toString().padStart(2, '0')}` : '',
        total_amount: Number((Math.random() * 20000 + 1000).toFixed(2)),
        status: ['待审', '已下单', '已入库', '已取消'][i % 4],
        remark: `备注信息${i + 1}`,
    }))
}

const tableData = ref<PurchaseOrder[]>(generateFakeOrders())
const currentPage = ref(1)
const pageSize = ref(8)
const dialogVisible = ref(false)
const dialogTitle = ref('添加采购订单')
const form = ref<Partial<PurchaseOrder>>({})
const formRef = ref<InstanceType<typeof import('element-plus').ElForm> | null>(null)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value).map(item => ({
        ...item,
        supplierName: suppliers.find(s => s.id === item.supplier_id)?.name ?? '',
    }))
})

const openDialog = (row?: PurchaseOrder) => {
    dialogTitle.value = row ? '编辑采购订单' : '添加采购订单'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    formRef.value?.validate(valid => {
        if (!valid) return
        if (form.value.purchase_order_id) {
            const index = tableData.value.findIndex(item => item.purchase_order_id === form.value.purchase_order_id)
            if (index !== -1) {
                tableData.value[index] = form.value as PurchaseOrder
            }
        } else {
            const newId = Date.now()
            tableData.value.push({ ...(form.value as PurchaseOrder), purchase_order_id: newId })
            form.value.purchase_order_id = newId
        }
        dialogVisible.value = false
    })
}

const handleDelete = (purchase_order_id: number) => {
    tableData.value = tableData.value.filter(item => item.purchase_order_id !== purchase_order_id)
    if (paginatedData.value.length === 0 && currentPage.value > 1) {
        currentPage.value--
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const rules = {
    supplier_id: [{ required: true, message: '请选择供应商', trigger: 'change' }],
    created_at: [{ required: true, message: '请选择创建时间', trigger: 'change' }],
    created_by: [{ required: true, message: '请输入创建人ID', trigger: 'blur' }],
    expected_arrival_date: [{ required: true, message: '请选择预计到货时间', trigger: 'change' }],
    total_amount: [{ required: true, type: 'number', message: '请输入总金额', trigger: 'blur' }],
    status: [{ required: true, message: '请选择订单状态', trigger: 'change' }],
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 16px;
}
</style>
