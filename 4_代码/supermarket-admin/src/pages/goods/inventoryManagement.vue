<template>
    <div class="app-container">
        <el-card>
            <template #header>
                <div class="flex justify-between items-center">
                    <el-button type="primary" @click="openDialog">新增库存</el-button>
                </div>
            </template>

            <el-table :data="tableData" stripe style="width: 100%">
                <el-table-column prop="id" label="ID" width="80" />
                <el-table-column prop="goods_id" label="商品ID" />
                <el-table-column prop="warehouse_id" label="仓库ID" />
                <el-table-column prop="quantity" label="库存数量" />
                <el-table-column prop="min_threshold" label="最小阈值" />
                <el-table-column prop="max_threshold" label="最大阈值" />
                <el-table-column prop="last_updated" label="最后更新时间" />
                <el-table-column label="操作" width="180">
                    <template #default="{ row }">
                        <el-button size="small" @click="openEditDialog(row)">编辑</el-button>
                        <el-button size="small" type="danger" @click="deleteInventory(row)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <div class="mt-4 text-right">
                <el-pagination v-model:current-page="pagination.page" :page-size="pagination.pageSize"
                    :total="pagination.total" layout="prev, pager, next" @current-change="loadData" />
            </div>
        </el-card>

        <el-dialog :title="formData.id ? '编辑库存' : '新增库存'" v-model="dialogVisible" width="500px">
            <el-form :model="formData" label-width="100px">
                <el-form-item label="商品ID">
                    <el-input v-model="formData.goods_id" />
                </el-form-item>
                <el-form-item label="仓库ID">
                    <el-input v-model="formData.warehouse_id" />
                </el-form-item>
                <el-form-item label="库存数量">
                    <el-input v-model.number="formData.quantity" type="number" />
                </el-form-item>
                <el-form-item label="最小阈值">
                    <el-input v-model.number="formData.min_threshold" type="number" />
                </el-form-item>
                <el-form-item label="最大阈值">
                    <el-input v-model.number="formData.max_threshold" type="number" />
                </el-form-item>
            </el-form>

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="saveInventory">保存</el-button>
            </template>
        </el-dialog>
    </div>
</template>

<script lang="ts" setup>
import { ref, reactive, onMounted } from 'vue'
import axios from 'axios'
import { ElMessage } from 'element-plus'

interface Inventory {
    id?: number
    goods_id?: string
    warehouse_id?: string
    quantity?: number
    min_threshold?: number
    max_threshold?: number
    last_updated?: string
}

const API_BASE = '/api/inventory'

const tableData = ref<Inventory[]>([])
const dialogVisible = ref(false)
const formData = reactive<Inventory>({
    id: undefined,
    goods_id: '',
    warehouse_id: '',
    quantity: 0,
    min_threshold: 0,
    max_threshold: 0,
    last_updated: '',
})

const pagination = reactive({
    page: 1,
    pageSize: 5,
    total: 0,
})

const loadData = async () => {
    try {
        const res = await axios.post(`${API_BASE}/get_by_page`, {
            page: pagination.page,
            page_size: pagination.pageSize
        })
        tableData.value = res.data.data.items || []
        pagination.total = res.data.data.total || 0
        ElMessage.success('加载成功') // 添加成功提示
    } catch (error) {
        ElMessage.error('加载数据失败')
    }
}


const openDialog = () => {
    Object.assign(formData, {
        id: undefined,
        goods_id: '',
        warehouse_id: '',
        quantity: 0,
        min_threshold: 0,
        max_threshold: 0,
        last_updated: '',
    })
    dialogVisible.value = true
}

const openEditDialog = (row: Inventory) => {
    Object.assign(formData, row)
    dialogVisible.value = true
}

const saveInventory = async () => {
    try {
        if (formData.id) {
            // 编辑
            await axios.post(`${API_BASE}/update`, formData)
        } else {
            // 新增
            await axios.post(`${API_BASE}/create`, formData)
        }
        ElMessage.success('保存成功')
        dialogVisible.value = false
        loadData()
    } catch (error) {
        ElMessage.error('保存失败')
    }
}

const deleteInventory = async (row: Inventory) => {
    if (!row.id) {
        ElMessage.warning('无效的ID，无法删除')
        return
    }
    try {
        await axios.post(`${API_BASE}/delete`, { id: row.id })
        ElMessage.success('删除成功')
        loadData()
    } catch (error) {
        ElMessage.error('删除失败')
    }
}

onMounted(() => {
    loadData()
})
</script>
