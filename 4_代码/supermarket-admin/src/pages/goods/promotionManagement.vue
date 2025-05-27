<template>
    <el-card>
        <h2>促销活动管理</h2>

        <el-button type="primary" @click="openCreateDialog" style="margin-bottom: 16px">添加促销活动</el-button>

        <el-table :data="pagedData" border>
            <el-table-column prop="promotion_id" label="ID" />
            <el-table-column prop="name" label="活动名称" />
            <el-table-column prop="description" label="活动描述" />
            <el-table-column prop="type" label="类型" />
            <el-table-column prop="start_time" label="开始时间" />
            <el-table-column prop="end_time" label="结束时间" />
            <el-table-column prop="status" label="状态" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="handleEdit(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.promotion_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <div class="pagination">
            <el-pagination :current-page="currentPage" :page-size="pageSize" :total="total"
                @current-change="handlePageChange" @size-change="handleSizeChange"
                layout="total, sizes, prev, pager, next, jumper" :page-sizes="[5, 10, 15]" />
        </div>

        <el-dialog v-model="dialogVisible" :title="isEdit ? '编辑促销活动' : '添加促销活动'" width="600px">
            <el-form :model="form" label-width="100px">
                <el-form-item label="活动名称">
                    <el-input v-model="form.name" placeholder="请输入活动名称" />
                </el-form-item>
                <el-form-item label="活动描述">
                    <el-input v-model="form.description" placeholder="请输入活动描述" />
                </el-form-item>
                <el-form-item label="类型">
                    <el-select v-model="form.type" placeholder="请选择类型">
                        <el-option label="折扣" value="discount" />
                        <el-option label="满减" value="full_reduction" />
                    </el-select>
                </el-form-item>
                <el-form-item label="开始时间">
                    <el-date-picker v-model="form.start_time" type="datetime" placeholder="请选择开始时间"
                        format="YYYY-MM-DD HH:mm:ss" value-format="YYYY-MM-DD HH:mm:ss" />
                </el-form-item>
                <el-form-item label="结束时间">
                    <el-date-picker v-model="form.end_time" type="datetime" placeholder="请选择结束时间"
                        format="YYYY-MM-DD HH:mm:ss" value-format="YYYY-MM-DD HH:mm:ss" />
                </el-form-item>
                <el-form-item label="状态">
                    <el-select v-model="form.status" placeholder="请选择状态">
                        <el-option label="激活" value="active" />
                        <el-option label="已过期" value="expired" />
                        <el-option label="草稿" value="draft" />
                    </el-select>
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSubmit">确认</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'

const dialogVisible = ref(false)
const isEdit = ref(false)
const useMock = true

const form = ref({
    promotion_id: null,
    name: '',
    description: '',
    type: 'discount',
    start_time: '',
    end_time: '',
    status: 'active'
})

const data = ref<any[]>([])
const currentPage = ref(1)
const pageSize = ref(5)
const total = ref(0)

const resetForm = () => {
    form.value = {
        promotion_id: null,
        name: '',
        description: '',
        type: 'discount',
        start_time: '',
        end_time: '',
        status: 'active'
    }
}

const generateMockData = () => {
    const types = ['discount', 'full_reduction']
    const statuses = ['active', 'expired', 'draft']
    const list = Array.from({ length: 25 }, (_, i) => {
        const start = new Date()
        start.setDate(start.getDate() - Math.floor(Math.random() * 10))
        const end = new Date(start)
        end.setDate(start.getDate() + Math.floor(Math.random() * 10))
        return {
            promotion_id: i + 1,
            name: `促销活动 ${i + 1}`,
            description: `描述 ${i + 1}`,
            type: types[i % 2],
            start_time: start.toISOString().slice(0, 19).replace('T', ' '),
            end_time: end.toISOString().slice(0, 19).replace('T', ' '),
            status: statuses[i % 3]
        }
    })
    data.value = list
    total.value = list.length
}

const pagedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return data.value.slice(start, start + pageSize.value)
})

const openCreateDialog = () => {
    resetForm()
    isEdit.value = false
    dialogVisible.value = true
}

const handleEdit = (row: any) => {
    form.value = { ...row }
    isEdit.value = true
    dialogVisible.value = true
}

const handleDelete = (id: number) => {
    data.value = data.value.filter(item => item.promotion_id !== id)
    total.value = data.value.length
}

const handleSubmit = () => {
    if (isEdit.value) {
        const index = data.value.findIndex(item => item.promotion_id === form.value.promotion_id)
        if (index !== -1) data.value[index] = { ...form.value }
    } else {
        const newId = data.value.length + 1
        data.value.push({ ...form.value, promotion_id: newId })
        total.value = data.value.length
    }
    dialogVisible.value = false
    resetForm()
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const handleSizeChange = (size: number) => {
    pageSize.value = size
    currentPage.value = 1
}

onMounted(() => {
    if (useMock) generateMockData()
})
</script>

<style scoped>
.pagination {
    margin-top: 16px;
    text-align: right;
}
</style>
