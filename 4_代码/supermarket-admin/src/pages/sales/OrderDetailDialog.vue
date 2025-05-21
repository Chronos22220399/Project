<template>
    <el-dialog :title="`订单 ${orderId || ''} 明细`" v-model="visible" width="900px" @close="resetState">
        <el-table :data="currentDetails" border height="300">
            <el-table-column prop="item_id" label="明细ID" width="100" />
            <el-table-column prop="product_name" label="商品名称" />
            <el-table-column prop="unit" label="单位" width="80" />
            <el-table-column prop="unit_price" label="单价" width="100" />
            <el-table-column prop="quantity" label="数量" width="80" />
            <el-table-column prop="subtotal" label="小计" width="100" />
            <el-table-column prop="promotion_id" label="促销 ID" width="100" />
            <el-table-column label="操作" width="180">
                <template #default="{ row }">
                    <el-button size="small" @click="editDetail(row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="deleteDetail(row.item_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <div class="text-right" style="margin-top: 12px;">
            <el-button type="primary" @click="addDetail">添加明细</el-button>
        </div>

        <!-- 明细编辑弹窗 -->
        <el-dialog title="编辑订单明细" v-model="detailFormVisible" width="500px" :before-close="handleDetailDialogClose">
            <el-form :model="detailForm" :rules="rules" ref="detailFormRef" label-width="100px">
                <el-form-item label="商品 ID" prop="goods_id">
                    <el-input v-model.number="detailForm.goods_id" type="number" />
                </el-form-item>
                <el-form-item label="商品名称" prop="product_name">
                    <el-input v-model="detailForm.product_name" />
                </el-form-item>
                <el-form-item label="单位" prop="unit">
                    <el-input v-model="detailForm.unit" />
                </el-form-item>
                <el-form-item label="单价" prop="unit_price">
                    <el-input v-model.number="detailForm.unit_price" type="number" min="0" step="0.01"
                        @input="updateSubtotal" />
                </el-form-item>
                <el-form-item label="数量" prop="quantity">
                    <el-input v-model.number="detailForm.quantity" type="number" min="1" @input="updateSubtotal" />
                </el-form-item>
                <el-form-item label="促销 ID" prop="promotion_id">
                    <el-input v-model.number="detailForm.promotion_id" type="number" />
                </el-form-item>
                <el-form-item label="小计">
                    <el-input :value="detailForm.subtotal.toFixed(2)" readonly />
                </el-form-item>
            </el-form>

            <template #footer>
                <el-button @click="detailFormVisible = false">取消</el-button>
                <el-button type="primary" @click="saveDetail">保存</el-button>
            </template>
        </el-dialog>
    </el-dialog>
</template>

<script setup lang="ts">
import { ref, reactive, computed, defineProps, defineExpose, nextTick } from 'vue'
import type { FormInstance } from 'element-plus'

interface OrderDetail {
    item_id: number
    order_id: number | null
    goods_id: number
    product_name: string
    unit: string
    unit_price: number
    quantity: number
    subtotal: number
    promotion_id: number | null
}

const props = defineProps<{
    orderId: number | null
}>()

const visible = ref(false)
const detailFormVisible = ref(false)
const allDetails = ref<OrderDetail[]>([])

const detailFormRef = ref<FormInstance>()

const detailForm = reactive<OrderDetail>({
    item_id: 0,
    order_id: null,
    goods_id: 0,
    product_name: '',
    unit: '',
    unit_price: 0,
    quantity: 1,
    subtotal: 0,
    promotion_id: null,
})

const currentDetails = computed(() => allDetails.value.filter(d => d.order_id === props.orderId))

const rules = {
    goods_id: [{ required: true, message: '请输入商品ID', trigger: 'blur' }],
    product_name: [{ required: true, message: '请输入商品名称', trigger: 'blur' }],
    unit: [{ required: true, message: '请输入单位', trigger: 'blur' }],
    unit_price: [
        { required: true, message: '请输入单价', trigger: 'blur' },
        { type: 'number', min: 0, message: '单价不能小于0', trigger: 'blur' },
    ],
    quantity: [
        { required: true, message: '请输入数量', trigger: 'blur' },
        { type: 'number', min: 1, message: '数量不能小于1', trigger: 'blur' },
    ],
}

function open(details: OrderDetail[]) {
    allDetails.value = details.map(d => ({ ...d }))
    visible.value = true
}

function resetState() {
    allDetails.value = []
    visible.value = false
    detailFormVisible.value = false
}

function addDetail() {
    Object.assign(detailForm, {
        item_id: Date.now(),
        order_id: props.orderId,
        goods_id: 0,
        product_name: '',
        unit: '',
        unit_price: 0,
        quantity: 1,
        subtotal: 0,
        promotion_id: null,
    })
    detailFormVisible.value = true
    nextTick(() => {
        detailFormRef.value?.clearValidate()
    })
}

function editDetail(row: OrderDetail) {
    Object.assign(detailForm, row)
    detailFormVisible.value = true
    nextTick(() => {
        detailFormRef.value?.clearValidate()
    })
}

function deleteDetail(id: number) {
    allDetails.value = allDetails.value.filter(d => d.item_id !== id)
}

function updateSubtotal() {
    detailForm.subtotal = parseFloat(((detailForm.unit_price || 0) * (detailForm.quantity || 0)).toFixed(2))
}

function saveDetail() {
    detailFormRef.value?.validate(valid => {
        if (!valid) return

        // 计算小计确保正确
        updateSubtotal()

        const idx = allDetails.value.findIndex(d => d.item_id === detailForm.item_id)
        if (idx === -1) {
            allDetails.value.push({ ...detailForm })
        } else {
            allDetails.value.splice(idx, 1, { ...detailForm })
        }
        detailFormVisible.value = false
    })
}

function handleDetailDialogClose(done: () => void) {
    // 关闭时清理验证状态
    detailFormRef.value?.clearValidate()
    done()
}

defineExpose({ open })
</script>

<style scoped>
.text-right {
    text-align: right;
}

.mt-4 {
    margin-top: 1rem;
}
</style>
