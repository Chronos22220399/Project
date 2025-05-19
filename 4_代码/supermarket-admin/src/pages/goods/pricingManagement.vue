<template>
    <el-card>
        <h2>商品价格管理</h2>
        <div class="product-price-management">
            <el-button type="primary" @click="openCreateDialog" style="margin-bottom: 16px">添加商品价格</el-button>

            <el-dialog :title="isEdit ? '编辑商品价格' : '添加商品价格'" v-model="dialogVisible" width="600px">
                <el-form :model="form" ref="form">
                    <el-form-item label="商品ID" :label-width="formLabelWidth">
                        <el-input v-model="form.product_id" placeholder="请输入商品ID" />
                    </el-form-item>
                    <el-form-item label="商品名称" :label-width="formLabelWidth">
                        <el-input v-model="form.product_name" placeholder="请输入商品名称" />
                    </el-form-item>
                    <el-form-item label="销售价格" :label-width="formLabelWidth">
                        <el-input-number v-model="form.price" :min="0" :step="0.01" placeholder="请输入价格" />
                    </el-form-item>
                </el-form>
                <template #footer>
                    <el-button @click="dialogVisible = false">取消</el-button>
                    <el-button type="primary" @click="handleDialogConfirm">确认</el-button>
                </template>
            </el-dialog>

            <el-table :data="pagedData" border style="margin-top: 24px">
                <el-table-column prop="id" label="价格ID" />
                <el-table-column prop="product_id" label="商品ID" />
                <el-table-column prop="product_name" label="商品名称" />
                <el-table-column prop="price" label="销售价格" />
                <el-table-column label="操作">
                    <template #default="scope">
                        <el-button size="small" @click="editItem(scope.row)">编辑</el-button>
                        <el-button size="small" type="danger" class="red-button"
                            @click="removeItem(scope.row.id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <div class="pagination">
                <el-pagination :current-page="currentPage" :page-size="pageSize" :total="totalItems"
                    @current-change="handlePageChange" @size-change="handlePageSizeChange"
                    layout="total, sizes, prev, pager, next, jumper" />
            </div>
        </div>
    </el-card>
</template>

<script setup>
import { ref, computed, onMounted } from 'vue'
import axios from 'axios'

const useMock = ref(true)
const dialogVisible = ref(false)
const isEdit = ref(false)

const priceList = ref([])
const currentPage = ref(1)
const pageSize = ref(5)
const totalItems = ref(0)

const form = ref({
    id: null,
    product_id: '',
    product_name: '',
    price: 0
})

const formLabelWidth = '120px'

const pagedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return priceList.value.slice(start, start + pageSize.value)
})

const handlePageChange = (page) => {
    currentPage.value = page
}

const handlePageSizeChange = (size) => {
    pageSize.value = size
    currentPage.value = 1
}

const fetchData = async () => {
    if (useMock.value) {
        priceList.value = generateMockData()
        totalItems.value = priceList.value.length
    } else {
        // 接口对接处
        const res = await axios.post('/api/price/list', {
            page: currentPage.value,
            page_size: pageSize.value
        })
        priceList.value = res.data.items
        totalItems.value = res.data.total
    }
}

const generateMockData = () => {
    return Array.from({ length: 25 }, (_, i) => ({
        id: i + 1,
        product_id: `P${1000 + i}`,
        product_name: `商品${i + 1}`,
        price: (Math.random() * 100).toFixed(2)
    }))
}

const openCreateDialog = () => {
    resetForm()
    isEdit.value = false
    dialogVisible.value = true
}

const editItem = (row) => {
    form.value = { ...row }
    isEdit.value = true
    dialogVisible.value = true
}

const handleDialogConfirm = () => {
    if (isEdit.value) {
        updateItem()
    } else {
        createItem()
    }
}

const createItem = () => {
    if (useMock.value) {
        const newId = priceList.value.length + 1
        priceList.value.push({ ...form.value, id: newId })
        totalItems.value = priceList.value.length
        dialogVisible.value = false
        resetForm()
    }
}

const updateItem = () => {
    if (useMock.value) {
        const index = priceList.value.findIndex(item => item.id === form.value.id)
        if (index !== -1) {
            priceList.value[index] = { ...form.value }
        }
        dialogVisible.value = false
        resetForm()
    }
}

const removeItem = (id) => {
    if (useMock.value) {
        priceList.value = priceList.value.filter(item => item.id !== id)
        totalItems.value = priceList.value.length
    }
}

const resetForm = () => {
    form.value = {
        id: null,
        product_id: '',
        product_name: '',
        price: 0
    }
}

onMounted(() => {
    fetchData()
})
</script>

<style scoped>
.product-price-management {
    padding: 20px;
}

.pagination {
    margin-top: 16px;
    text-align: right;
}

.el-table .el-button {
    margin-right: 10px;
}

.el-table .el-button--text.red-button {
    color: red;
}
</style>
