<template>
    <div>
        <el-button type="primary" @click="openDialog">新增商品价格</el-button>

        <el-table :data="tableData" style="width: 100%; margin-top: 20px">
            <el-table-column prop="id" label="ID" width="100" />
            <el-table-column prop="goods_rk_id" label="入库ID" width="150" />
            <el-table-column prop="price" label="价格" width="120" />
            <el-table-column prop="start_time" label="开始时间" width="180" />
            <el-table-column prop="note" label="备注" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="getDetail(scope.row.id)">详情</el-button>
                    <el-button size="small" type="danger" @click="deletePrice(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-model:current-page="pagination.page" :page-size="pagination.pageSize" :total="pagination.total"
            layout="total, prev, pager, next" @current-change="fetchPrices" class="mt-4" />

        <el-dialog v-model="dialogVisible" title="新增商品价格" width="600px">
            <el-form :model="form" label-width="120px">
                <el-form-item label="入库ID">
                    <el-input v-model="form.goods_rk_id" />
                </el-form-item>
                <el-form-item label="价格">
                    <el-input type="number" v-model.number="form.price" />
                </el-form-item>
                <el-form-item label="开始时间">
                    <el-date-picker v-model="form.start_time" type="datetime" placeholder="选择时间" style="width: 100%" />
                </el-form-item>
                <el-form-item label="备注">
                    <el-input v-model="form.note" type="textarea" />
                </el-form-item>
            </el-form>

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="createPrice">创建</el-button>
            </template>
        </el-dialog>
    </div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from 'vue'
import { ElMessage } from 'element-plus'
import axios from 'axios'

const API_BASE = '/api/goods_price'

const tableData = ref<any[]>([])
const pagination = reactive({
    page: 1,
    pageSize: 5,
    total: 0,
})

const dialogVisible = ref(false)

const form = reactive({
    id: '',
    goods_rk_id: '',
    price: 0,
    start_time: '',
    note: '',
})

// 打开新增弹窗
const openDialog = () => {
    Object.assign(form, {
        id: '',
        goods_rk_id: '',
        price: 0,
        start_time: '',
        note: '',
    })
    dialogVisible.value = true
}

const fetchPrices = async (page = pagination.page) => {
    try {
        const res = await axios.post(`${API_BASE}/get_by_page`, {
            page,
            page_size: pagination.pageSize,
        })
        const data = res.data
        if (data.code === 200) {
            tableData.value = data.data.items
            pagination.total = data.data.total
            pagination.page = page
            ElMessage.success('数据加载成功')
        } else {
            ElMessage.error(data.error || '加载失败')
        }
    } catch {
        ElMessage.error('网络请求失败')
    }
}

const createPrice = async () => {
    try {
        const res = await axios.post(`${API_BASE}/create`, form)
        const data = res.data
        if (data.code === 200) {
            ElMessage.success('创建成功')
            dialogVisible.value = false
            fetchPrices()
        } else {
            ElMessage.error(data.error || '创建失败')
        }
    } catch {
        ElMessage.error('网络请求失败')
    }
}

const getDetail = (id: string) => {
    // 这里可以写获取详情逻辑，打开详情弹窗等
    ElMessage.info(`请求获取ID为${id}的价格详情`)
}

const deletePrice = async (id: string) => {
    try {
        const res = await axios.post(`${API_BASE}/remove`, { id })
        const data = res.data
        if (data.code === 200) {
            ElMessage.success('删除成功')
            fetchPrices()
        } else {
            ElMessage.error(data.error || '删除失败')
        }
    } catch {
        ElMessage.error('网络请求失败')
    }
}

onMounted(() => {
    fetchPrices()
})
</script>
