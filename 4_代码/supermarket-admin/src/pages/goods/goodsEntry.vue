<template>
    <div>
        <!-- 正常页面内容 -->
        <el-button type="primary" @click="openDialog">新增商品</el-button>

        <!-- 表格 -->
        <el-table :data="tableData" style="width: 100%; margin-top: 20px">
            <el-table-column prop="goods_id" label="商品ID" width="150" />
            <el-table-column prop="goods_name" label="名称" />
            <el-table-column prop="category_name" label="分类" />
            <el-table-column prop="stock" label="库存" width="100" />
            <el-table-column label="操作" width="160">
                <template #default="scope">
                    <el-button size="small" @click="getDetail(scope.row.goods_id)">详情</el-button>
                </template>
            </el-table-column>
        </el-table>

        <!-- 分页 -->
        <el-pagination v-model:current-page="pagination.page" :page-size="pagination.pageSize" :total="pagination.total"
            layout="total, prev, pager, next" @current-change="fetchGoods" class="mt-4" />

        <!-- 新增商品弹窗 -->
        <el-dialog v-model="dialogVisible" title="新增商品" width="600px">
            <el-form :model="form" label-width="100px">
                <el-form-item label="商品名称">
                    <el-input v-model="form.goods_name" />
                </el-form-item>
                <el-form-item label="分类ID">
                    <el-input v-model="form.goods_category_id" />
                </el-form-item>
                <el-form-item label="供应商ID">
                    <el-input v-model="form.supplier_id" />
                </el-form-item>
                <el-form-item label="单位ID">
                    <el-input v-model="form.unit_id" />
                </el-form-item>
                <el-form-item label="保质期(天)">
                    <el-input type="number" v-model.number="form.shelf_life_days" />
                </el-form-item>
                <el-form-item label="条形码">
                    <el-input v-model="form.barcode" />
                </el-form-item>
                <el-form-item label="图片URL">
                    <el-input v-model="form.image_url" />
                </el-form-item>
                <el-form-item label="描述">
                    <el-input v-model="form.description" type="textarea" />
                </el-form-item>
            </el-form>

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="createGoods">创建</el-button>
            </template>
        </el-dialog>

        <!-- 商品详情弹窗 -->
        <el-dialog v-model="detailDialogVisible" title="商品详情" width="500px">
            <el-descriptions :column="1" border>
                <el-descriptions-item label="商品ID">{{ detail.goods_id }}</el-descriptions-item>
                <el-descriptions-item label="商品名称">{{ detail.goods_name }}</el-descriptions-item>
                <el-descriptions-item label="库存">{{ detail.quantity }}</el-descriptions-item>
                <el-descriptions-item label="单位">{{ detail.unit }}</el-descriptions-item>
                <el-descriptions-item label="仓库">{{ detail.warehouse_name }}</el-descriptions-item>
                <el-descriptions-item label="位置">{{ detail.location }}</el-descriptions-item>
                <el-descriptions-item label="保质期">{{ detail.shelf_life_days }} 天</el-descriptions-item>
            </el-descriptions>
        </el-dialog>
    </div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from 'vue'
import { ElMessage } from 'element-plus'
import axios from 'axios'

const API_BASE = '/api/goods'

const tableData = ref([
    {
        goods_id: '1',
        goods_name: '测试商品A',
        category_name: '饮料',
        stock: 100,
    },
    {
        goods_id: '2',
        goods_name: '测试商品B',
        category_name: '食品',
        stock: 50,
    },
    {
        goods_id: '3',
        goods_name: '测试商品C',
        category_name: '日用品',
        stock: 200,
    },
])

const pagination = reactive({
    page: 1,
    pageSize: 10,
    total: 3,
})

const dialogVisible = ref(false)
const detailDialogVisible = ref(false)
const form = reactive({
    goods_id: '',
    goods_name: '',
    goods_category_id: '',
    supplier_id: '',
    unit_id: '',
    shelf_life_days: 365,
    barcode: '',
    image_url: '',
    description: '',
})
const detail = reactive({
    goods_id: '',
    goods_name: '',
    quantity: 0,
    unit: '',
    warehouse_name: '',
    location: '',
    shelf_life_days: 0,
})

// 业务功能方法

const fetchGoods = async (page = pagination.page) => {
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
            ElMessage.success('成功获取后端数据')
        } else {
            ElMessage.error(data.error || '获取商品失败')
        }
    } catch (error) {
        ElMessage.error('网络请求失败')
    }
}

const createGoods = async () => {
    try {
        const res = await axios.post(`${API_BASE}/create`, form)
        const data = res.data
        if (data.code === 200) {
            ElMessage.success('创建成功')
            dialogVisible.value = false
            fetchGoods()
        } else {
            ElMessage.error(data.error || '创建失败')
        }
    } catch (error) {
        ElMessage.error('网络请求失败')
    }
}

const getDetail = async (goods_id: string) => {
    try {
        const res = await axios.post(`${API_BASE}/get_goods_detail_info`, { goods_id })
        const data = res.data
        if (data.code === 200) {
            Object.assign(detail, data.data)
            detailDialogVisible.value = true
        } else {
            ElMessage.error(data.error || '获取详情失败')
        }
    } catch (error) {
        ElMessage.error('网络请求失败')
    }
}

const openDialog = () => {
    Object.assign(form, {
        goods_id: '',
        goods_name: '',
        goods_category_id: '',
        supplier_id: '',
        unit_id: '',
        shelf_life_days: 365,
        barcode: '',
        image_url: '',
        description: '',
    })
    dialogVisible.value = true
}

onMounted(() => {
    fetchGoods()
})
</script>
