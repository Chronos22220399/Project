<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加退货记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="returnId" label="退货ID" width="100" />
            <el-table-column prop="orderId" label="原订单ID" />
            <el-table-column prop="returnReason" label="退货原因" />
            <el-table-column prop="returnDate" label="退货日期" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.returnId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />
        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="原订单ID"><el-input v-model="form.orderId" /></el-form-item>
                <el-form-item label="退货原因"><el-input v-model="form.returnReason" /></el-form-item>
                <el-form-item label="退货日期"><el-date-picker v-model="form.returnDate" type="date" /></el-form-item>
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

interface SalesReturn {
    returnId: number
    orderId: number
    returnReason: string
    returnDate: string
}

const tableData = ref<SalesReturn[]>(Array.from({ length: 20 }, (_, i) => ({
    returnId: i + 1,
    orderId: 100 + i,
    returnReason: '客户不满意',
    returnDate: '2025-05-02'
})))

const pageSize = ref(10)
const currentPage = ref(1)
const dialogVisible = ref(false)
const dialogTitle = ref('添加退货记录')
const form = ref<Partial<SalesReturn>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SalesReturn) => {
    dialogTitle.value = row ? '编辑退货记录' : '添加退货记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.returnId) {
        const index = tableData.value.findIndex(item => item.returnId === form.value.returnId)
        if (index !== -1) tableData.value[index] = { ...(form.value as SalesReturn) }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as SalesReturn), returnId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (returnId: number) => {
    tableData.value = tableData.value.filter(item => item.returnId !== returnId)
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
