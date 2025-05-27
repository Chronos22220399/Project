<template>
    <div class="p-4">
        <el-card>
            <div class="flex justify-between items-center mb-4">
                <el-button type="primary" @click="openDialog()">新增入库单</el-button>
            </div>
            <el-table :data="tableData" stripe style="width: 100%">
                <el-table-column prop="stock_in_id" label="入库单号" width="120" />
                <el-table-column prop="warehouse_id" label="仓库ID" />
                <el-table-column prop="created_at" label="创建时间" />
                <el-table-column prop="created_by" label="创建人" />
                <el-table-column prop="source_type" label="来源类型" />
                <el-table-column prop="source_reference" label="来源单据号" />
                <el-table-column prop="status" label="状态" />
                <el-table-column prop="remark" label="备注" />
                <el-table-column label="操作" width="180">
                    <template #default="scope">
                        <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                        <el-button size="small" type="danger" @click="remove(scope.row.stock_in_id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <el-pagination class="mt-4" background layout="prev, pager, next" :total="total" :page-size="pageSize"
                @current-change="handlePageChange" />
        </el-card>

        <el-dialog v-model="dialogVisible" :title="formData.stock_in_id ? '编辑入库单' : '新增入库单'">
            <el-form :model="formData" label-width="100px">
                <el-form-item label="仓库ID">
                    <el-input v-model="formData.warehouse_id" />
                </el-form-item>
                <el-form-item label="创建人">
                    <el-input v-model="formData.created_by" />
                </el-form-item>
                <el-form-item label="来源类型">
                    <el-input v-model="formData.source_type" />
                </el-form-item>
                <el-form-item label="来源单据号">
                    <el-input v-model="formData.source_reference" />
                </el-form-item>
                <el-form-item label="状态">
                    <el-input v-model="formData.status" />
                </el-form-item>
                <el-form-item label="备注">
                    <el-input type="textarea" v-model="formData.remark" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="submitForm">保存</el-button>
            </template>
        </el-dialog>
    </div>
</template>

<script lang="ts" setup>
import { ref, onMounted } from 'vue'
import axios from 'axios'
import { ElMessage, ElMessageBox } from 'element-plus'

interface StockInOrder {
    stock_in_id?: number
    warehouse_id: number
    created_at?: string
    created_by: string
    source_type: string
    source_reference: string
    status: string
    remark: string
}

const tableData = ref<StockInOrder[]>([])
const total = ref(0)
const pageSize = 5
const currentPage = ref(1)

const dialogVisible = ref(false)
const formData = ref<StockInOrder>({
    warehouse_id: 0,
    created_by: '',
    source_type: '',
    source_reference: '',
    status: '',
    remark: '',
})

const fetchData = async () => {
    try {
        const res = await axios.post('/api/stock_in/getByPage', {
            page: currentPage.value,
            page_size: pageSize,
        })
        if (res.data && res.data.data) {
            tableData.value = res.data.data.items
            total.value = res.data.data.total
        }
    } catch (err) {
        ElMessage.error('获取数据失败')
    }
}

const openDialog = (row?: StockInOrder) => {
    dialogVisible.value = true
    if (row) {
        formData.value = { ...row }
    } else {
        formData.value = {
            warehouse_id: 0,
            created_by: '',
            source_type: '',
            source_reference: '',
            status: '',
            remark: '',
        }
    }
}

const submitForm = async () => {
    try {
        if (formData.value.stock_in_id) {
            await axios.post('/api/stock_in/update', formData.value)
            ElMessage.success('更新成功')
        } else {
            await axios.post('/api/stock_in/create', formData.value)
            ElMessage.success('创建成功')
        }
        dialogVisible.value = false
        fetchData()
    } catch (err) {
        ElMessage.error('操作失败')
    }
}

const remove = async (id: number) => {
    try {
        await ElMessageBox.confirm('确定删除此入库单？', '提示', { type: 'warning' })
        await axios.post('/api/stock_in/remove', { stock_in_id: id })
        ElMessage.success('删除成功')
        fetchData()
    } catch (err) {
        ElMessage.info('已取消删除')
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
    fetchData()
}

onMounted(fetchData)
</script>
