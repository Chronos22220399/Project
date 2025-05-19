<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加成本记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="productId" label="商品ID" width="120" />
            <el-table-column prop="totalInboundPrice" label="入库总价" />
            <el-table-column prop="outboundQuantity" label="出库数量" />
            <el-table-column prop="costAmount" label="成本金额" />
            <el-table-column prop="calculationTime" label="计算时间" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.productId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="商品ID"><el-input v-model="form.productId" /></el-form-item>
                <el-form-item label="入库总价"><el-input v-model="form.totalInboundPrice" /></el-form-item>
                <el-form-item label="出库数量"><el-input v-model="form.outboundQuantity" /></el-form-item>
                <el-form-item label="成本金额"><el-input v-model="form.costAmount" /></el-form-item>
                <el-form-item label="计算时间"><el-date-picker v-model="form.calculationTime" type="date" /></el-form-item>
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

interface CostRecord {
    productId: number
    totalInboundPrice: number
    outboundQuantity: number
    costAmount: number
    calculationTime: string
}

const generateFakeCostRecords = (): CostRecord[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        productId: 1000 + i,
        totalInboundPrice: Number((Math.random() * 10000).toFixed(2)),
        outboundQuantity: Math.floor(Math.random() * 100),
        costAmount: Number((Math.random() * 8000).toFixed(2)),
        calculationTime: '2025-05-01'
    }))
}

const tableData = ref < CostRecord[] > (generateFakeCostRecords())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加成本记录')
const form = ref < Partial < CostRecord >> ({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: CostRecord) => {
    dialogTitle.value = row ? '编辑成本记录' : '添加成本记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.productId) {
        const index = tableData.value.findIndex(item => item.productId === form.value.productId)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as CostRecord) }
        }
    } else {
        const newId = Date.now()
        // 这里新加的productId用时间戳做唯一值
        tableData.value.push({ ...(form.value as CostRecord), productId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (productId: number) => {
    tableData.value = tableData.value.filter(item => item.productId !== productId)
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
