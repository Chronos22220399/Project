<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加仓库</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="仓库ID" width="100" />
            <el-table-column prop="name" label="仓库名" />
            <el-table-column prop="address" label="地址" />
            <el-table-column prop="capacity" label="容量" />
            <el-table-column prop="superintendent" label="负责人" />
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
                <el-form-item label="仓库名"><el-input v-model="form.name" /></el-form-item>
                <el-form-item label="地址"><el-input v-model="form.address" /></el-form-item>
                <el-form-item label="容量"><el-input v-model="form.capacity" /></el-form-item>
                <el-form-item label="负责人"><el-input v-model="form.superintendent" /></el-form-item>
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
import axios from 'axios'

interface Warehouse {
    id: number
    name: string
    address: string
    capacity: string
    superintendent: string
}

// 假数据（仅用于展示，正式接入 API 后可去掉）
const generateFakeData = () => {
    return Array.from({ length: 50 }, (_, index) => ({
        id: index + 1,
        name: `仓库${index + 1}`,
        address: `地址${index + 1}`,
        capacity: `${Math.floor(Math.random() * 1000) + 500}`,
        superintendent: `负责人${index + 1}`,
    }))
}

const tableData = ref<Warehouse[]>(generateFakeData())
const dialogVisible = ref(false)
const dialogTitle = ref('添加仓库')
const form = ref<Partial<Warehouse>>({})

// 分页控制
const currentPage = ref(1)
const pageSize = ref(10)
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

// 打开弹窗
const openDialog = (row?: Warehouse) => {
    dialogTitle.value = row ? '编辑仓库' : '添加仓库'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

// 保存（新增或编辑）
const handleSave = async () => {
    const warehouseData = {
        id: form.value.id,
        name: form.value.name,
        address: form.value.address,
        capacity: form.value.capacity,
        superintendent: form.value.superintendent
    }

    try {
        let response
        if (form.value.id) {
            // 编辑仓库
            response = await axios.put(`/api/warehouse/${form.value.id}`, warehouseData)
        } else {
            // 添加仓库
            response = await axios.post('/api/warehouse', warehouseData)
        }

        console.log('请求成功', response.data)

        if (form.value.id) {
            // 本地更新编辑
            const index = tableData.value.findIndex(item => item.id === form.value.id)
            if (index !== -1) {
                tableData.value[index] = { ...(form.value as Warehouse) }
            }
        } else {
            // 添加返回 ID（可根据后端返回调整）
            const newId = response.data.id || Date.now()
            tableData.value.push({ ...(form.value as Warehouse), id: newId })
        }

        dialogVisible.value = false
    } catch (error) {
        console.error('保存失败', error)
    }
}

// 删除仓库
const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/warehouse/${id}`)
        tableData.value = tableData.value.filter(item => item.id !== id)
    } catch (error) {
        console.error('删除失败', error)
    }
}

// 翻页处理
const handlePageChange = (page: number) => {
    currentPage.value = page
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
