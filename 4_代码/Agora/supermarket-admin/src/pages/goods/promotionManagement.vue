<template>
    <div class="promotion-page p-4">
        <el-card class="mb-4">
            <div class="flex justify-between items-center">
                <el-button type="primary" @click="openCreateDialog">新增促销</el-button>
            </div>
        </el-card>

        <el-card>
            <el-table :data="promotions" stripe style="width: 100%">
                <el-table-column prop="promotion_id" label="ID" width="160" />
                <el-table-column prop="name" label="名称" />
                <el-table-column prop="description" label="描述" />
                <el-table-column prop="type" label="类型" width="140" />
                <el-table-column prop="start_time" label="开始时间" width="180" />
                <el-table-column prop="end_time" label="结束时间" width="180" />
                <el-table-column prop="status" label="状态" width="120" />
                <el-table-column label="操作" width="200">
                    <template #default="scope">
                        <el-button size="small" @click="openEditDialog(scope.row)">编辑</el-button>
                        <el-button size="small" type="danger" @click="deleteRow(scope.row.promotion_id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <el-pagination class="mt-4" background layout="total, prev, pager, next" :total="total"
                :current-page.sync="page" :page-size="pageSize" @current-change="loadData" />
        </el-card>

        <el-dialog :title="isEdit ? '编辑促销' : '新增促销'" v-model="dialogVisible" width="600px">
            <el-form :model="form" label-width="100px">
                <el-form-item label="名称">
                    <el-input v-model="form.name" />
                </el-form-item>
                <el-form-item label="描述">
                    <el-input v-model="form.description" />
                </el-form-item>
                <el-form-item label="类型">
                    <el-select v-model="form.type" placeholder="请选择类型">
                        <el-option label="折扣" value="discount" />
                        <el-option label="满减" value="full reduction" />
                    </el-select>
                </el-form-item>
                <el-form-item label="开始时间">
                    <el-date-picker v-model="form.start_time" type="datetime" />
                </el-form-item>
                <el-form-item label="结束时间">
                    <el-date-picker v-model="form.end_time" type="datetime" />
                </el-form-item>
                <el-form-item label="状态">
                    <el-select v-model="form.status">
                        <el-option label="启用" value="active" />
                        <el-option label="草稿" value="draft" />
                        <el-option label="过期" value="expired" />
                    </el-select>
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSubmit">保存</el-button>
            </template>
        </el-dialog>
    </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import {
    getPromotionsByPage,
    createPromotion,
    updatePromotion,
    deletePromotion,
    type Promotion,
} from '../../api/goods_api/promotion.ts'
import { ElMessage, ElMessageBox } from 'element-plus'

const promotions = ref<Promotion[]>([])
const total = ref(0)
const page = ref(1)
const pageSize = ref(10)

const dialogVisible = ref(false)
const isEdit = ref(false)
const form = ref<Promotion>({
    promotion_id: '',
    name: '',
    description: '',
    type: 'discount',
    start_time: '',
    end_time: '',
    status: 'draft'
})

const loadData = async () => {
    const res = await getPromotionsByPage({ page: page.value, page_size: pageSize.value })
    promotions.value = res.data.data
    total.value = res.data.total
}

const openCreateDialog = () => {
    isEdit.value = false
    dialogVisible.value = true
    form.value = {
        promotion_id: '',
        name: '',
        description: '',
        type: 'discount',
        start_time: '',
        end_time: '',
        status: 'draft'
    }
}

const openEditDialog = (row: Promotion) => {
    isEdit.value = true
    dialogVisible.value = true
    form.value = { ...row }
}

const handleSubmit = async () => {
    const submitData = { ...form.value }
    if (isEdit.value) {
        await updatePromotion(submitData)
        ElMessage.success('更新成功')
    } else {
        await createPromotion(submitData)
        ElMessage.success('创建成功')
    }
    dialogVisible.value = false
    loadData()
}

const deleteRow = (id: string) => {
    ElMessageBox.confirm('确认删除该促销信息？', '提示', {
        type: 'warning'
    }).then(async () => {
        await deletePromotion({ promotion_id: id })
        ElMessage.success('删除成功')
        loadData()
    })
}

onMounted(loadData)
</script>

<style scoped>
.promotion-page .el-card {
    margin-bottom: 16px;
}
</style>