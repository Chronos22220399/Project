<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加盘点单</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="盘点单ID" width="120" />
            <el-table-column prop="warehouseId" label="仓库ID" width="120" />
            <el-table-column prop="time" label="盘点时间" width="180" />
            <el-table-column prop="remark" label="备注" />
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

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="800px" :before-close="handleDialogClose">
            <el-form :model="form" label-width="100px">
                <el-form-item label="仓库ID">
                    <el-input v-model="form.warehouseId" />
                </el-form-item>
                <el-form-item label="盘点时间">
                    <el-date-picker v-model="form.time" type="datetime" placeholder="选择时间" />
                </el-form-item>
                <el-form-item label="备注">
                    <el-input v-model="form.remark" />
                </el-form-item>
            </el-form>

            <!-- 嵌套明细表组件 -->
            <inventory-check-details v-model:details="form.details" />

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSave">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import InventoryCheckDetails from './InventoryCheckDetails.vue'

interface InventoryCheckItem {
    id: number | string
    productId: string
    counted: number
    actual: number
    difference: number
}

interface InventoryCheck {
    id: number | string
    warehouseId: string
    time: string
    remark: string
    details: InventoryCheckItem[]
}

const generateFakeData = (): InventoryCheck[] => {
    return Array.from({ length: 20 }, (_, idx) => ({
        id: idx + 1,
        warehouseId: `W${idx + 1}`,
        time: `2023-05-${String(idx + 1).padStart(2, '0')} 10:00:00`,
        remark: `备注信息${idx + 1}`,
        details: Array.from({ length: 3 }, (__, j) => {
            const counted = Math.floor(Math.random() * 100)
            const actual = Math.floor(Math.random() * 100)
            return {
                id: `${idx + 1}-${j + 1}`,
                productId: `P${j + 1}`,
                counted,
                actual,
                difference: counted - actual,
            }
        }),
    }))
}

const tableData = ref<InventoryCheck[]>(generateFakeData())

const dialogVisible = ref(false)
const dialogTitle = ref('添加盘点单')

const form = ref<Omit<InventoryCheck, 'id'> & { id?: string | number }>({
    warehouseId: '',
    time: '',
    remark: '',
    details: [],
})

const currentPage = ref(1)
const pageSize = ref(10)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: InventoryCheck) => {
    dialogTitle.value = row ? '编辑盘点单' : '添加盘点单'
    if (row) {
        form.value = {
            ...row,
            details: row.details.map(item => ({ ...item })),
        }
    } else {
        form.value = {
            id: '',
            warehouseId: '',
            time: '',
            remark: '',
            details: [],
        }
    }
    dialogVisible.value = true
}

const handleSave = () => {
    if (!form.value.warehouseId || !form.value.time) {
        alert('请填写仓库ID和盘点时间')
        return
    }
    form.value.details?.forEach(item => {
        item.difference = (item.counted || 0) - (item.actual || 0)
    })
    if (form.value.id) {
        const idx = tableData.value.findIndex(item => item.id === form.value.id)
        if (idx !== -1) tableData.value[idx] = form.value as InventoryCheck
    } else {
        form.value.id = Date.now()
        tableData.value.push(form.value as InventoryCheck)
    }
    dialogVisible.value = false
}

const handleDelete = (id: number | string) => {
    tableData.value = tableData.value.filter(item => item.id !== id)
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const handleDialogClose = (done: () => void) => {
    done()
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
