<template>
    <el-dialog :title="`退货单 ${returnId || ''} 明细`" v-model="visible" width="800px" @close="resetState">
        <el-table :data="details" border style="width: 100%" height="300">
            <el-table-column prop="item_id" label="明细ID" width="100" />
            <el-table-column prop="goods_id" label="商品ID" width="100" />
            <el-table-column prop="product_name" label="商品名称" />
            <el-table-column prop="original_quantity" label="原销售数量" width="120" />
            <el-table-column prop="return_quantity" label="退货数量" width="120" />
            <el-table-column prop="unit_price" label="单价" width="100" />
            <el-table-column prop="refund_amount" label="退款金额" width="120" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="onEdit(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="onDelete(scope.row.item_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <div style="margin-top: 10px;">
            <el-button type="primary" @click="onAdd">新增明细</el-button>
        </div>

        <el-dialog title="编辑退货明细" v-model="editVisible" width="500px" :before-close="handleEditDialogClose">
            <el-form :model="editForm" label-width="120px" ref="editFormRef">
                <el-form-item label="商品ID" prop="goods_id"
                    :rules="[{ required: true, message: '请输入商品ID', trigger: 'blur' }]">
                    <el-input v-model.number="editForm.goods_id" type="number" />
                </el-form-item>
                <el-form-item label="商品名称" prop="product_name"
                    :rules="[{ required: true, message: '请输入商品名称', trigger: 'blur' }]">
                    <el-input v-model="editForm.product_name" />
                </el-form-item>
                <el-form-item label="原销售数量" prop="original_quantity"
                    :rules="[{ required: true, message: '请输入原销售数量', trigger: 'blur' }]">
                    <el-input v-model.number="editForm.original_quantity" type="number" min="1" />
                </el-form-item>
                <el-form-item label="退货数量" prop="return_quantity" :rules="[
                    { required: true, message: '请输入退货数量', trigger: 'blur' },
                    { validator: validateReturnQuantity, trigger: 'blur' }
                ]">
                    <el-input v-model.number="editForm.return_quantity" type="number" min="1" />
                </el-form-item>
                <el-form-item label="单价" prop="unit_price"
                    :rules="[{ required: true, message: '请输入单价', trigger: 'blur' }]">
                    <el-input v-model.number="editForm.unit_price" type="number" min="0" step="0.01" />
                </el-form-item>
                <el-form-item label="退款金额">
                    <el-input :value="computedRefundAmount" disabled />
                </el-form-item>
            </el-form>

            <template #footer>
                <el-button @click="editVisible = false">取消</el-button>
                <el-button type="primary" @click="saveEdit">保存</el-button>
            </template>
        </el-dialog>
    </el-dialog>
</template>

<script setup lang="ts">
import { ref, reactive, computed } from 'vue'
import type { FormInstance } from 'element-plus'

interface ReturnDetail {
    item_id: number
    return_id: number
    goods_id: number
    product_name: string
    original_quantity: number
    return_quantity: number
    unit_price: number
    refund_amount: number
}

const visible = ref(false)
const returnId = ref<number | null>(null)
const details = ref<ReturnDetail[]>([])

const editVisible = ref(false)
const editForm = reactive<Partial<ReturnDetail>>({
    item_id: 0,
    return_id: 0,
    goods_id: 0,
    product_name: '',
    original_quantity: 1,
    return_quantity: 1,
    unit_price: 0,
    refund_amount: 0,
})

const editFormRef = ref<FormInstance>()

// 计算退款金额 = 单价 × 退货数量
const computedRefundAmount = computed(() => {
    const unit = editForm.unit_price || 0
    const qty = editForm.return_quantity || 0
    return (unit * qty).toFixed(2)
})

// 打开明细弹窗并传入数据
function open(data: ReturnDetail[]) {
    if (data.length > 0) {
        returnId.value = data[0].return_id
    } else {
        returnId.value = null
    }
    details.value = data.map(item => ({ ...item }))
    visible.value = true
}

function resetState() {
    details.value = []
    returnId.value = null
}

// 新增明细
function onAdd() {
    Object.assign(editForm, {
        item_id: Date.now(),
        return_id: returnId.value,
        goods_id: 0,
        product_name: '',
        original_quantity: 1,
        return_quantity: 1,
        unit_price: 0,
        refund_amount: 0,
    })
    editVisible.value = true
}

// 编辑明细
function onEdit(row: ReturnDetail) {
    Object.assign(editForm, row)
    editVisible.value = true
}

// 删除明细
function onDelete(item_id: number) {
    details.value = details.value.filter(item => item.item_id !== item_id)
}

// 验证退货数量不超过原销售数量
function validateReturnQuantity(rule: any, value: number, callback: Function) {
    if (value > (editForm.original_quantity || 0)) {
        callback(new Error('退货数量不能超过原销售数量'))
    } else {
        callback()
    }
}

function saveEdit() {
    editFormRef.value?.validate(valid => {
        if (!valid) return

        // 更新退款金额
        editForm.refund_amount = parseFloat(computedRefundAmount.value)

        // 判断是新增还是编辑
        const idx = details.value.findIndex(item => item.item_id === editForm.item_id)
        if (idx === -1) {
            details.value.push({ ...(editForm as ReturnDetail) })
        } else {
            details.value[idx] = { ...(editForm as ReturnDetail) }
        }
        editVisible.value = false
    })
}

function handleEditDialogClose(done: Function) {
    // 可加弹窗关闭确认逻辑
    done()
}

defineExpose({ open })
</script>

<style scoped>
.el-table {
    margin-bottom: 10px;
}
</style>
