<template>
    <div>
        <el-table :data="items" style="width: 100%" border size="small" :row-key="(row: StockInItem) => row.item_id">
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

interface StockInItem {
    item_id: number
    goods_id: string
    quantity: number
    remark: string
}

const props = defineProps<{
    modelValue: StockInItem[]
}>()

const emit = defineEmits<{
    (e: 'update:modelValue', value: StockInItem[]): void
}>()

import { reactive } from 'vue'
const items = reactive<StockInItem[]>([])

watch(
    () => props.modelValue,
    (newVal) => {
        items.splice(0, items.length, ...newVal.map(item => ({ ...item })))
    },
    { immediate: true, deep: true }
)

function addItem() {
    items.push({
        item_id: Date.now(),
        goods_id: '',
        quantity: 1,
        remark: '',
    })
    emit('update:modelValue', items)
}

function removeItem(index: number) {
    items.splice(index, 1)
    emit('update:modelValue', items)
}

function updateItem(index: number, row: StockInItem) {
    items[index] = { ...row }
    emit('update:modelValue', items)
}
</script>
