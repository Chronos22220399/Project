<template>
    <div>
        <el-button size="small" type="primary" @click="addDetailRow">添加明细</el-button>
        <el-table :data="details" border size="small" style="margin-top: 10px">
            <el-table-column prop="productId" label="商品ID" width="150">
                <template #default="{ row }">
                    <el-input v-model="row.productId" size="small" />
                </template>
            </el-table-column>
            <el-table-column prop="counted" label="盘点数量" width="120">
                <template #default="{ row }">
                    <el-input-number v-model="row.counted" size="small" :min="0" @change="updateDifference(row)" />
                </template>
            </el-table-column>
            <el-table-column prop="actual" label="实际数量" width="120">
                <template #default="{ row }">
                    <el-input-number v-model="row.actual" size="small" :min="0" @change="updateDifference(row)" />
                </template>
            </el-table-column>
            <el-table-column prop="difference" label="差异" width="100">
                <template #default="{ row }">{{ row.difference }}</template>
            </el-table-column>
            <el-table-column label="操作" width="100">
                <template #default="{ $index }">
                    <el-button type="danger" icon="el-icon-delete" size="small" @click="removeDetailRow($index)" />
                </template>
            </el-table-column>
        </el-table>
    </div>
</template>

<script setup lang="ts">
import { defineProps, defineEmits } from 'vue'

interface InventoryCheckItem {
    id: number | string
    productId: string
    counted: number
    actual: number
    difference: number
}

const props = defineProps<{
    details: InventoryCheckItem[]
}>()

const emit = defineEmits<{
    (e: 'update:details', val: InventoryCheckItem[]): void
}>()

const addDetailRow = () => {
    const newRow: InventoryCheckItem = {
        id: Date.now().toString(),
        productId: '',
        counted: 0,
        actual: 0,
        difference: 0,
    }
    props.details.push(newRow)
    emit('update:details', props.details)
}

const removeDetailRow = (index: number) => {
    props.details.splice(index, 1)
    emit('update:details', props.details)
}

const updateDifference = (row: InventoryCheckItem) => {
    row.difference = (row.counted || 0) - (row.actual || 0)
    emit('update:details', props.details)
}
</script>
