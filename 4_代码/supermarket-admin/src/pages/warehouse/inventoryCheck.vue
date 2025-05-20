<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加盘点记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="记录ID" width="100" />
            <el-table-column prop="warehouseId" label="仓库ID" />
            <el-table-column prop="productId" label="商品ID" />
            <el-table-column prop="counted" label="盘点数量" />
            <el-table-column prop="actual" label="实际数量" />
            <el-table-column prop="difference" label="差异" />
            <el-table-column prop="time" label="时间" />
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
                <el-form-item label="盘点数量"><el-input v-model="form.counted" /></el-form-item>
                <el-form-item label="实际数量"><el-input v-model="form.actual" /></el-form-item>
                <el-form-item label="时间"><el-date-picker v-model="form.time" type="datetime" /></el-form-item>
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

interface Inventory {
    id: number
    warehouseId: string
    productId: string
    counted: number
    actual: number
    difference: number
    time: string
}

// 假数据生成
const generateFakeData = () => {
    return Array.from({ length: 50 }, (_, index) => ({
        id: index + 1,
        warehouseId: `W${index + 1}`,
        productId: `P${index + 1}`,
        counted: Math.floor(Math.random() * 100) + 1,
        actual: Math.floor(Math.random() * 100) + 1,
        difference: 0,
        time: `2021-01-${String(index + 1).padStart(2, '0')} 00:00:00`,
    }))
}

const tableData = ref<Inventory[]>(generateFakeData())  // 假数据
const dialogVisible = ref(false)
const dialogTitle = ref('添加盘点记录')
const form = ref<Partial<Inventory>>({})

// 分页控制
const currentPage = ref(1)
const pageSize = ref(10)

// 计算分页后的数据
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    const end = start + pageSize.value
    return tableData.value.slice(start, end)
})


const openDialog = (row?: Inventory) => {
    dialogTitle.value = row ? '编辑盘点记录' : '添加盘点记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.id) {
        const index = tableData.value.findIndex(item => item.id === form.value.id)
        if (index !== -1) tableData.value[index] = form.value as Inventory
    } else {
        form.value.id = Date.now()
        form.value.difference = (form.value.counted || 0) - (form.value.actual || 0)
        tableData.value.push(form.value as Inventory)
    }
    dialogVisible.value = false
}

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
