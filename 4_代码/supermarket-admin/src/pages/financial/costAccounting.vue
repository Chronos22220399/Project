<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加成本记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="costRecordId" label="成本记录ID" width="120" />
            <el-table-column prop="goodsId" label="商品ID" />
            <el-table-column prop="inboundId" label="入库单ID" />
            <el-table-column prop="supplierId" label="供应商ID" />
            <el-table-column prop="unitCost" label="单位成本" />
            <el-table-column prop="quantity" label="数量" />
            <el-table-column prop="totalCost" label="总成本" />
            <el-table-column prop="inboundTime" label="入库时间" />
            <el-table-column prop="recordedAt" label="记录时间" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.costRecordId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="商品ID"><el-input v-model="form.goodsId" /></el-form-item>
                <el-form-item label="入库单ID"><el-input v-model="form.inboundId" /></el-form-item>
                <el-form-item label="供应商ID"><el-input v-model="form.supplierId" /></el-form-item>
                <el-form-item label="单位成本"><el-input v-model="form.unitCost" /></el-form-item>
                <el-form-item label="数量"><el-input v-model="form.quantity" /></el-form-item>
                <el-form-item label="总成本"><el-input v-model="form.totalCost" /></el-form-item>
                <el-form-item label="入库时间"><el-date-picker v-model="form.inboundTime" type="datetime" /></el-form-item>
                <el-form-item label="记录时间"><el-date-picker v-model="form.recordedAt" type="datetime" /></el-form-item>
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

interface GoodsCostRecord {
    costRecordId: number
    goodsId: number
    inboundId: number
    supplierId: number
    unitCost: number
    quantity: number
    totalCost: number
    inboundTime: string
    recordedAt: string
}

const generateFakeCostRecords = (): GoodsCostRecord[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        costRecordId: i + 1,
        goodsId: 1000 + i,
        inboundId: 2000 + i,
        supplierId: 3000 + i,
        unitCost: Number((Math.random() * 100).toFixed(2)),
        quantity: Math.floor(Math.random() * 100) + 1,
        totalCost: 0,
        inboundTime: '2025-05-01 10:00:00',
        recordedAt: '2025-05-21 09:00:00'
    })).map(item => ({
        ...item,
        totalCost: Number((item.unitCost * item.quantity).toFixed(2))
    }))
}

const tableData = ref<GoodsCostRecord[]>(generateFakeCostRecords())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加成本记录')
const form = ref<Partial<GoodsCostRecord>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: GoodsCostRecord) => {
    dialogTitle.value = row ? '编辑成本记录' : '添加成本记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.costRecordId) {
        const index = tableData.value.findIndex(item => item.costRecordId === form.value.costRecordId)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as GoodsCostRecord) }
        }
    } else {
        const newId = Date.now()
        tableData.value.push({
            ...(form.value as GoodsCostRecord),
            costRecordId: newId
        })
    }
    dialogVisible.value = false
}

const handleDelete = (costRecordId: number) => {
    tableData.value = tableData.value.filter(item => item.costRecordId !== costRecordId)
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
