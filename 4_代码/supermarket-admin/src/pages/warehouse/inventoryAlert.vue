<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加库存明细</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="item_id" label="明细ID" width="120" />
            <el-table-column prop="inventory_id" label="库存ID" width="120" />
            <el-table-column prop="min_threshold" label="安全库存下限" width="150" />
            <el-table-column prop="max_threshold" label="安全库存上限" width="150" />
            <el-table-column prop="last_updated" label="最后更新日期" width="180" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.item_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="120px" ref="formRef">
                <el-form-item label="库存ID" prop="inventory_id" required>
                    <el-input v-model="form.inventory_id" autocomplete="off" />
                </el-form-item>
                <el-form-item label="安全库存下限" prop="min_threshold" required>
                    <el-input-number v-model="form.min_threshold" :min="0" />
                </el-form-item>
                <el-form-item label="安全库存上限" prop="max_threshold" required>
                    <el-input-number v-model="form.max_threshold" :min="0" />
                </el-form-item>
                <el-form-item label="最后更新日期" prop="last_updated" required>
                    <el-date-picker v-model="form.last_updated" type="datetime" placeholder="选择日期时间" style="width: 100%"
                        value-format="yyyy-MM-dd HH:mm:ss" />
                </el-form-item>
                <el-form-item label="备注" prop="remark">
                    <el-input v-model="form.remark" autocomplete="off" />
                </el-form-item>
            </el-form>

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSave">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed, reactive } from 'vue'
import dayjs from 'dayjs'

interface InventoryItem {
    item_id: number
    inventory_id: string
    min_threshold: number
    max_threshold: number
    last_updated: string // ISO 字符串格式
    remark?: string
}

// 生成假数据
const generateFakeData = (): InventoryItem[] => {
    return Array.from({ length: 50 }, (_, i) => ({
        item_id: i + 1,
        inventory_id: `INV${i + 1}`,
        min_threshold: Math.floor(Math.random() * 50),
        max_threshold: Math.floor(Math.random() * 100 + 50),
        last_updated: dayjs().subtract(i, 'day').format('YYYY-MM-DD HH:mm:ss'),
        remark: `备注${i + 1}`,
    }))
}

const tableData = ref<InventoryItem[]>(generateFakeData())
const dialogVisible = ref(false)
const dialogTitle = ref('添加库存明细')
const form = reactive<Partial<InventoryItem>>({})

const currentPage = ref(1)
const pageSize = ref(10)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: InventoryItem) => {
    if (row) {
        dialogTitle.value = '编辑库存明细'
        Object.assign(form, row)
    } else {
        dialogTitle.value = '添加库存明细'
        Object.assign(form, {
            item_id: 0,
            inventory_id: '',
            min_threshold: 0,
            max_threshold: 0,
            last_updated: dayjs().format('YYYY-MM-DD HH:mm:ss'),
            remark: '',
        })
    }
    dialogVisible.value = true
}

const handleSave = () => {
    if (!form.inventory_id || form.min_threshold == null || form.max_threshold == null || !form.last_updated) {
        alert('请填写完整必填项')
        return
    }
    if (form.item_id && form.item_id !== 0) {
        // 更新
        const index = tableData.value.findIndex(item => item.item_id === form.item_id)
        if (index !== -1) {
            tableData.value[index] = { ...(form as InventoryItem) }
        }
    } else {
        // 新增，生成 item_id
        form.item_id = Date.now()
        tableData.value.push(form as InventoryItem)
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.item_id !== id)
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
