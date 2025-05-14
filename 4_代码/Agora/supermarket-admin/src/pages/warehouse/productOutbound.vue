<!-- src/views/warehouse/Outbound.vue -->
<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加出库记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="记录ID" width="100" />
            <el-table-column prop="warehouseId" label="仓库ID" />
            <el-table-column prop="productId" label="商品ID" />
            <el-table-column prop="unitId" label="单位ID" />
            <el-table-column prop="quantity" label="数量" />
            <el-table-column prop="reason" label="原因" />
            <el-table-column prop="outboundTime" label="出库时间" />
            <el-table-column prop="operator" label="操作员" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="仓库ID"><el-input v-model="form.warehouseId" /></el-form-item>
                <el-form-item label="商品ID"><el-input v-model="form.productId" /></el-form-item>
                <el-form-item label="单位ID"><el-input v-model="form.unitId" /></el-form-item>
                <el-form-item label="数量"><el-input v-model="form.quantity" /></el-form-item>
                <el-form-item label="原因"><el-input v-model="form.reason" /></el-form-item>
                <el-form-item label="出库时间"><el-date-picker v-model="form.outboundTime" type="datetime" /></el-form-item>
                <el-form-item label="操作员"><el-input v-model="form.operator" /></el-form-item>
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

interface Outbound {
    id: number
    warehouseId: string
    productId: string
    unitId: string
    quantity: number
    reason: string
    outboundTime: string
    operator: string
}

// 假数据生成
const generateFakeData = () => {
    return Array.from({ length: 50 }, (_, index) => ({
        id: index + 1,
        warehouseId: `W${index + 1}`,
        productId: `P${index + 1}`,
        unitId: `U${index + 1}`,
        quantity: Math.floor(Math.random() * 100) + 1,
        reason: `Reason ${index + 1}`,
        outboundTime: `2021-01-${String(index + 1).padStart(2, '0')} 00:00:00`,
        operator: `Operator ${index + 1}`
    }))
}

const tableData = ref<Outbound[]>(generateFakeData())  // 假数据
const dialogVisible = ref(false)
const dialogTitle = ref('添加出库记录')
const form = ref<Partial<Outbound>>({})

// 分页控制
const currentPage = ref(1)
const pageSize = ref(10)

// 计算分页后的数据
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    const end = start + pageSize.value
    return tableData.value.slice(start, end)
})

// 打开对话框
const openDialog = (row?: Outbound) => {
    dialogTitle.value = row ? '编辑出库记录' : '添加出库记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

// 保存操作
const handleSave = () => {
    if (form.value.id) {
        const index = tableData.value.findIndex(item => item.id === form.value.id)
        if (index !== -1) tableData.value[index] = form.value as Outbound
    } else {
        form.value.id = Date.now()
        tableData.value.push(form.value as Outbound)
    }
    dialogVisible.value = false
}

// 删除操作
const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.id !== id)
}

// 分页切换
const handlePageChange = (page: number) => {
    currentPage.value = page
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
