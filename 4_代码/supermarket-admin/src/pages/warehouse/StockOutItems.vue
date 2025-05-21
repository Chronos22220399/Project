<template>
    <div>
        <el-table :data="items" style="width: 100%" border size="small" :row-key="(row: StockOutItem) => row.item_id">
            <el-table-column prop="goods_id" label="商品ID" width="140">
                <template #default="{ row, $index }">
                    <el-input v-model="row.goods_id" placeholder="请输入商品ID" @input="updateItem($index, row)" />
                </template>
            </el-table-column>

            <el-table-column prop="quantity" label="数量" width="100">
                <template #default="{ row, $index }">
                    <el-input-number v-model="row.quantity" :min="1" @change="updateItem($index, row)" />
                </template>
            </el-table-column>

            <el-table-column prop="price" label="单价" width="120">
                <template #default="{ row, $index }">
                    <el-input-number v-model="row.price" :min="0" :step="0.01" precision="2"
                        @change="updateItem($index, row)" />
                </template>
            </el-table-column>

            <el-table-column prop="amount" label="金额" width="120">
                <template #default="{ row }">
                    <el-input-number :model-value="row.quantity * row.price" :disabled="true" precision="2" />
                </template>
            </el-table-column>

            <el-table-column label="备注" width="180">
                <template #default="{ row, $index }">
                    <el-input v-model="row.remark" placeholder="备注" @input="updateItem($index, row)" />
                </template>
            </el-table-column>

            <el-table-column label="操作" width="120">
                <template #default="{ $index }">
                    <el-button type="danger" icon="el-icon-delete" circle @click="removeItem($index)" />
                </template>
            </el-table-column>
        </el-table>

        <el-button type="primary" plain size="small" icon="el-icon-plus" @click="addItem" style="margin-top: 8px">
            添加明细
        </el-button>
    </div>
</template>

<script setup lang="ts">
import { defineProps, defineEmits, watch } from 'vue'

interface StockOutItem {
    item_id: number
    goods_id: string
    quantity: number
    price: number
    remark: string
}

// 父组件传入的明细数组
const props = defineProps<{
    modelValue: StockOutItem[]
}>()

const emit = defineEmits<{
    (e: 'update:modelValue', value: StockOutItem[]): void
}>()

// 因为 prop 是只读的，自己复制一份响应式处理
import { reactive, toRefs } from 'vue'
const items = reactive<StockOutItem[]>([])

// 初始化 items
watch(
    () => props.modelValue,
    (newVal) => {
        items.splice(0, items.length, ...newVal.map(item => ({ ...item })))
    },
    { immediate: true, deep: true }
)

// 添加一条明细
function addItem() {
    items.push({
        item_id: Date.now(),
        goods_id: '',
        quantity: 1,
        price: 0,
        remark: '',
    })
    emit('update:modelValue', items)
}

// 删除一条明细
function removeItem(index: number) {
    items.splice(index, 1)
    emit('update:modelValue', items)
}

// 当单条明细更新，通知父组件
function updateItem(index: number, row: StockOutItem) {
    items[index] = { ...row }
    emit('update:modelValue', items)
}
</script>
