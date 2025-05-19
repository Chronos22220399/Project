<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加评价</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="reviewId" label="评价ID" width="100" />
            <el-table-column prop="supplierName" label="供应商名称" />
            <el-table-column prop="reviewer" label="评价人" />
            <el-table-column prop="rating" label="评分" width="100" />
            <el-table-column prop="comment" label="评价内容" />
            <el-table-column label="操作" width="160">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.reviewId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 12px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="520px">
            <el-form :model="form" label-width="110px" ref="formRef">
                <el-form-item label="供应商名称" prop="supplierName"
                    :rules="[{ required: true, message: '请输入供应商名称', trigger: 'blur' }]">
                    <el-input v-model="form.supplierName" />
                </el-form-item>
                <el-form-item label="评价人" prop="reviewer"
                    :rules="[{ required: true, message: '请输入评价人', trigger: 'blur' }]">
                    <el-input v-model="form.reviewer" />
                </el-form-item>
                <el-form-item label="评分" prop="rating"
                    :rules="[{ required: true, type: 'number', message: '请选择评分', trigger: 'change' }]">
                    <el-rate v-model="form.rating" :max="5" />
                </el-form-item>
                <el-form-item label="评价内容" prop="comment"
                    :rules="[{ required: true, message: '请输入评价内容', trigger: 'blur' }]">
                    <el-input type="textarea" v-model="form.comment" rows="3" />
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
import type { Ref } from 'vue'

interface SupplierReview {
    reviewId: number
    supplierName: string
    reviewer: string
    rating: number
    comment: string
}

const generateFakeReviews = (): SupplierReview[] => {
    return Array.from({ length: 25 }, (_, i) => ({
        reviewId: i + 1,
        supplierName: `供应商-${(i % 10) + 1}`,
        reviewer: `评价人-${i + 1}`,
        rating: (i % 5) + 1,
        comment: `这是第${i + 1}条评价内容示例。`
    }))
}

const tableData = ref<SupplierReview[]>(generateFakeReviews())
const currentPage = ref(1)
const pageSize = ref(8)
const dialogVisible = ref(false)
const dialogTitle = ref('添加评价')
const form = ref<Partial<SupplierReview>>({})
const formRef = ref<InstanceType<typeof import('element-plus').ElForm> | null>(null)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SupplierReview) => {
    dialogTitle.value = row ? '编辑评价' : '添加评价'
    form.value = row ? { ...row } : { rating: 0 }
    dialogVisible.value = true
}

const handleSave = () => {
    formRef.value?.validate(valid => {
        if (!valid) return
        if (form.value.reviewId) {
            const index = tableData.value.findIndex(item => item.reviewId === form.value.reviewId)
            if (index !== -1) {
                tableData.value[index] = form.value as SupplierReview
            }
        } else {
            const newId = Date.now()
            tableData.value.push({ ...(form.value as SupplierReview), reviewId: newId })
        }
        dialogVisible.value = false
    })
}

const handleDelete = (reviewId: number) => {
    tableData.value = tableData.value.filter(item => item.reviewId !== reviewId)
    if (paginatedData.value.length === 0 && currentPage.value > 1) {
        currentPage.value--
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 16px;
}
</style>
