<template>
    <el-card>
        <h2>商品价格管理</h2>
        <div>
            <el-button type="primary" @click="openCreateDialog" style="margin-bottom: 16px">添加商品价格</el-button>

            <el-dialog v-model="dialogVisible" :title="isEdit ? '编辑商品价格' : '添加商品价格'" width="600px">
                <el-form :model="form" label-width="100px" ref="formRef">
                    <el-form-item label="商品名称">
                        <el-input v-model="form.product_name" placeholder="请输入商品名称" />
                    </el-form-item>
                    <el-form-item label="销售价格">
                        <el-input-number v-model="form.price" :min="0" :step="0.01" placeholder="请输入销售价格" />
                    </el-form-item>
                    <el-form-item label="开始时间">
                        <el-date-picker v-model="form.start_time" type="datetime" placeholder="请选择开始时间"
                            format="YYYY-MM-DD HH:mm:ss" value-format="YYYY-MM-DD HH:mm:ss" />
                    </el-form-item>
                    <el-form-item label="备注">
                        <el-input v-model="form.remark" type="textarea" :rows="3" placeholder="请输入备注信息" />
                    </el-form-item>
                </el-form>
                <template #footer>
                    <el-button @click="dialogVisible = false">取消</el-button>
                    <el-button type="primary" @click="handleDialogConfirm">确认</el-button>
                </template>
            </el-dialog>

            <el-table :data="pagedData" border style="margin-top: 24px">
                <el-table-column prop="id" label="价格ID" width="100" />
                <el-table-column prop="product_name" label="商品名称" />
                <el-table-column prop="price" label="销售价格" />
                <el-table-column prop="start_time" label="开始时间" />
                <el-table-column prop="remark" label="备注" />
                <el-table-column label="操作" width="180">

                    <template #default="scope">
                        <el-button size="small" @click="editItem(scope.row)">更新</el-button>
                        <el-button type="danger" size="small" @click="removeItem(scope.row.id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <div class="pagination">
                <el-pagination :current-page="currentPage" :page-size="pageSize" :total="totalItems"
                    layout="total, sizes, prev, pager, next, jumper" @current-change="handlePageChange"
                    @size-change="handlePageSizeChange" />
            </div>
        </div>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import axios from 'axios'

const useMock = ref(true)
const dialogVisible = ref(false)
const isEdit = ref(false)

const formRef = ref()
const form = ref({
    id: null,
    product_id: '',
    product_name: '',
    price: 0,
    start_time: '',
    remark: ''
})

const priceList = ref<any[]>([])
const currentPage = ref(1)
const pageSize = ref(5)
const totalItems = ref(0)

const pagedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return priceList.value.slice(start, start + pageSize.value)
})

const openCreateDialog = () => {
    resetForm()
    isEdit.value = false
    dialogVisible.value = true
}

const editItem = (row: any) => {
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
        const newId = priceList.value.length ? Math.max(...priceList.value.map(i => i.id)) + 1 : 1
        priceList.value.push({ ...form.value, id: newId })
        totalItems.value = priceList.value.length
        dialogVisible.value = false
        resetForm()
    } else {
        // 调用后端 API 创建
    }
}

const updateItem = () => {
    if (useMock.value) {
        const index = priceList.value.findIndex(item => item.id === form.value.id)
        if (index !== -1) priceList.value[index] = { ...form.value }
        dialogVisible.value = false
        resetForm()
    } else {
        // 调用后端 API 更新
    }
}

const removeItem = (id: number) => {
    if (useMock.value) {
        priceList.value = priceList.value.filter(item => item.id !== id)
        totalItems.value = priceList.value.length
    } else {
        // 调用后端 API 删除
    }
}

const resetForm = () => {
    form.value = {
        id: null,
        product_id: '',
        product_name: '',
        price: 0,
        start_time: '',
        remark: ''
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const handlePageSizeChange = (size: number) => {
    pageSize.value = size
    currentPage.value = 1
}

const fetchData = async () => {
    if (useMock.value) {
        priceList.value = Array.from({ length: 50 }, (_, i) => ({
            id: i + 1,
            product_id: `P${1000 + i}`,
            product_name: `商品${i + 1}`,
            price: (Math.random() * 100).toFixed(2),
            start_time: new Date().toISOString().slice(0, 19).replace('T', ' '),
            remark: `备注${i + 1}`
        }))
        totalItems.value = priceList.value.length
    } else {
        const res = await axios.post('/api/price/list', {
            page: currentPage.value,
            page_size: pageSize.value
        })
        priceList.value = res.data.items
        totalItems.value = res.data.total
    }
}

onMounted(() => {
    fetchData()
})
</script>

<style scoped>
.pagination {
    margin-top: 16px;
    text-align: right;
}
</style>
