<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加仓库</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="warehouse_id" label="仓库ID" width="100" />
            <el-table-column prop="name" label="仓库名" />
            <el-table-column prop="address" label="地址" />
            <el-table-column prop="capacity" label="容量" />
            <el-table-column prop="phone" label="联系电话" />
            <el-table-column prop="admin_id" label="管理员ID" />
            <el-table-column prop="status" label="状态" />
            <el-table-column prop="created_at" label="创建时间" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.warehouse_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="仓库名">
                    <el-input v-model="form.name" />
                </el-form-item>
                <el-form-item label="地址">
                    <el-input v-model="form.address" />
                </el-form-item>
                <el-form-item label="容量">
                    <el-input v-model="form.capacity" type="number" />
                </el-form-item>
                <el-form-item label="联系电话">
                    <el-input v-model="form.phone" />
                </el-form-item>
                <el-form-item label="管理员ID">
                    <el-input v-model="form.admin_id" type="number" />
                </el-form-item>
                <el-form-item label="状态">
                    <el-select v-model="form.status" placeholder="请选择状态">
                        <el-option label="启用" :value="1" />
                        <el-option label="禁用" :value="0" />
                    </el-select>
                </el-form-item>
                <el-form-item label="备注">
                    <el-input type="textarea" v-model="form.remark" />
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
import { ref, computed } from 'vue'
import axios from 'axios'

interface Warehouse {
    warehouse_id: number
    name: string
    address: string
    capacity: number
    phone: string
    admin_id: number
    status: number
    created_at?: string
    remark?: string
}

const generateFakeData = () => {
    return Array.from({ length: 50 }, (_, index) => ({
        warehouse_id: index + 1,
        name: `仓库${index + 1}`,
        address: `地址${index + 1}`,
        capacity: Math.floor(Math.random() * 1000) + 500,
        phone: `1380000${String(index + 1).padStart(4, '0')}`,
        admin_id: index + 200,
        status: index % 2,
        created_at: new Date().toISOString().slice(0, 19).replace('T', ' '),
        remark: `备注${index + 1}`
    }))
}

const tableData = ref<Warehouse[]>(generateFakeData())
const dialogVisible = ref(false)
const dialogTitle = ref('添加仓库')
const form = ref<Partial<Warehouse>>({})

const currentPage = ref(1)
const pageSize = ref(10)
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: Warehouse) => {
    dialogTitle.value = row ? '编辑仓库' : '添加仓库'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = async () => {
    const warehouseData = {
        warehouse_id: form.value.warehouse_id,
        name: form.value.name,
        address: form.value.address,
        capacity: form.value.capacity,
        phone: form.value.phone,
        admin_id: form.value.admin_id,
        status: form.value.status,
        remark: form.value.remark
    }

    try {
        let response
        if (form.value.warehouse_id) {
            response = await axios.put(`/api/warehouse/${form.value.warehouse_id}`, warehouseData)
        } else {
            response = await axios.post('/api/warehouse', warehouseData)
        }

        console.log('请求成功', response.data)

        if (form.value.warehouse_id) {
            const index = tableData.value.findIndex(item => item.warehouse_id === form.value.warehouse_id)
            if (index !== -1) {
                tableData.value[index] = {
                    ...(form.value as Warehouse),
                    created_at: tableData.value[index].created_at
                }
            }
        } else {
            const newId = response.data.warehouse_id || Date.now()
            tableData.value.push({
                ...(form.value as Warehouse),
                warehouse_id: newId,
                created_at: new Date().toISOString().slice(0, 19).replace('T', ' ')
            })
        }

        dialogVisible.value = false
    } catch (error) {
        console.error('保存失败', error)
    }
}

const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/warehouse/${id}`)
        tableData.value = tableData.value.filter(item => item.warehouse_id !== id)
    } catch (error) {
        console.error('删除失败', error)
    }
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
