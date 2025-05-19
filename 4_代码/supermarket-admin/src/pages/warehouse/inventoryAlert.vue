<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加预警规则</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="预警ID" width="100" />
            <el-table-column prop="productId" label="商品ID" />
            <el-table-column prop="warehouseId" label="仓库ID" />
            <el-table-column prop="threshold" label="库存下限" />
            <el-table-column prop="currentStock" label="当前库存" />
            <el-table-column prop="status" label="状态">
                <template #default="scope">
                    <el-tag :type="scope.row.currentStock < scope.row.threshold ? 'danger' : 'success'">
                        {{ scope.row.currentStock < scope.row.threshold ? '预警' : '正常' }} </el-tag>
                </template>
            </el-table-column>
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
                <el-form-item label="商品ID"><el-input v-model="form.productId" /></el-form-item>
                <el-form-item label="仓库ID"><el-input v-model="form.warehouseId" /></el-form-item>
                <el-form-item label="库存下限"><el-input v-model="form.threshold" type="number" /></el-form-item>
                <el-form-item label="当前库存"><el-input v-model="form.currentStock" type="number" /></el-form-item>
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

interface Warning {
    id: number
    productId: string
    warehouseId: string
    threshold: number
    currentStock: number
}

// 假数据生成
const generateFakeData = () => {
    return Array.from({ length: 50 }, (_, index) => ({
        id: index + 1,
        productId: `P${index + 1}`,
        warehouseId: `W${index + 1}`,
        threshold: Math.floor(Math.random() * 50) + 10,
        currentStock: Math.floor(Math.random() * 100) + 1,
    }))
}

const tableData = ref<Warning[]>(generateFakeData())  // 假数据
const dialogVisible = ref(false)
const dialogTitle = ref('添加预警规则')
const form = ref<Partial<Warning>>({})

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
const openDialog = (row?: Warning) => {
    dialogTitle.value = row ? '编辑预警规则' : '添加预警规则'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

// 保存数据
const handleSave = () => {
    if (form.value.id) {
        const index = tableData.value.findIndex(item => item.id === form.value.id)
        if (index !== -1) tableData.value[index] = form.value as Warning
    } else {
        form.value.id = Date.now()
        tableData.value.push(form.value as Warning)
    }
    dialogVisible.value = false
}

// 删除数据
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
