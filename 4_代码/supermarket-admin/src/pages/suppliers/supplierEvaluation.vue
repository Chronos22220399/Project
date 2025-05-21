<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加评价</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="evaluation_id" label="评价ID" width="100" />
            <el-table-column prop="supplier_id" label="供应商名称" />
            <el-table-column prop="evaluator_id" label="评价人员" />
            <el-table-column prop="evaluation_date" label="评价时间" width="160" />
            <el-table-column prop="service_score" label="服务评分" width="100" />
            <el-table-column prop="qualify_score" label="供货质量评分" width="100" />
            <el-table-column prop="timeliness_score" label="供货及时性评分" width="100" />
            <el-table-column prop="total_score" label="总评分" width="100" />
            <el-table-column prop="comment" label="综合评价" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="160">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.evaluation_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 12px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="600px">
            <el-form :model="form" label-width="130px" ref="formRef" :rules="rules">
                <el-form-item label="供应商" prop="supplier_id">
                    <el-select v-model="form.supplier_id" placeholder="请选择供应商">
                        <el-option v-for="supplier in suppliers" :key="supplier.id" :label="supplier.name"
                            :value="supplier.id" />
                    </el-select>
                </el-form-item>

                <el-form-item label="评价人员" prop="evaluator_id">
                    <el-select v-model="form.evaluator_id" placeholder="请选择评价人员">
                        <el-option v-for="evaluator in evaluators" :key="evaluator.id" :label="evaluator.name"
                            :value="evaluator.id" />
                    </el-select>
                </el-form-item>

                <el-form-item label="评价时间" prop="evaluation_date">
                    <el-date-picker v-model="form.evaluation_date" type="date" placeholder="选择评价时间"
                        style="width: 100%" />
                </el-form-item>

                <el-form-item label="服务评分" prop="service_score">
                    <el-rate v-model="form.service_score" :max="5" @change="updateTotalScore" />
                </el-form-item>

                <el-form-item label="供货质量评分" prop="qualify_score">
                    <el-rate v-model="form.qualify_score" :max="5" @change="updateTotalScore" />
                </el-form-item>

                <el-form-item label="供货及时性评分" prop="timeliness_score">
                    <el-rate v-model="form.timeliness_score" :max="5" @change="updateTotalScore" />
                </el-form-item>

                <el-form-item label="总评分" prop="total_score">
                    <el-input v-model="form.total_score" disabled />
                </el-form-item>

                <el-form-item label="综合评价" prop="comment">
                    <el-input type="textarea" v-model="form.comment" rows="3" />
                </el-form-item>

                <el-form-item label="备注" prop="remark">
                    <el-input v-model="form.remark" />
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

interface SupplierEvaluation {
    evaluation_id: number
    supplier_id: number
    evaluation_date: string
    evaluator_id: number
    service_score: number
    qualify_score: number
    timeliness_score: number
    comment: string
    total_score: number
    remark?: string
}

interface Supplier {
    id: number
    name: string
}

interface Evaluator {
    id: number
    name: string
}

// 模拟供应商列表
const suppliers: Supplier[] = Array.from({ length: 10 }, (_, i) => ({
    id: i + 1,
    name: `供应商-${i + 1}`,
}))

// 模拟员工评价人员列表
const evaluators: Evaluator[] = Array.from({ length: 5 }, (_, i) => ({
    id: i + 1,
    name: `员工-${i + 1}`,
}))

// 生成假数据
const generateFakeEvaluations = (): SupplierEvaluation[] => {
    return Array.from({ length: 25 }, (_, i) => ({
        evaluation_id: i + 1,
        supplier_id: ((i % 10) + 1),
        evaluation_date: `2025-05-${(i % 28) + 1 < 10 ? '0' : ''}${(i % 28) + 1}`,
        evaluator_id: ((i % 5) + 1),
        service_score: (i % 5) + 1,
        qualify_score: (i + 1) % 5 + 1,
        timeliness_score: ((i + 2) % 5) + 1,
        comment: `这是第${i + 1}条综合评价示例。`,
        total_score: 0,
        remark: `备注信息${i + 1}`
    })).map(item => {
        item.total_score = item.service_score + item.qualify_score + item.timeliness_score
        return item
    })
}

const tableData = ref<SupplierEvaluation[]>(generateFakeEvaluations())

const currentPage = ref(1)
const pageSize = ref(8)
const dialogVisible = ref(false)
const dialogTitle = ref('添加评价')

const form = ref<Partial<SupplierEvaluation>>({})
const formRef = ref<InstanceType<typeof import('element-plus').ElForm> | null>(null)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value
        .slice(start, start + pageSize.value)
        .map(item => ({
            ...item,
            supplierName: suppliers.find(s => s.id === item.supplier_id)?.name ?? '',
            evaluatorName: evaluators.find(e => e.id === item.evaluator_id)?.name ?? '',
        }))
})

const openDialog = (row?: SupplierEvaluation) => {
    dialogTitle.value = row ? '编辑评价' : '添加评价'
    form.value = row
        ? { ...row }
        : {
            service_score: 0,
            qualify_score: 0,
            timeliness_score: 0,
            total_score: 0,
            evaluation_date: '',
        }
    dialogVisible.value = true
}

const updateTotalScore = () => {
    form.value.total_score =
        (form.value.service_score ?? 0) +
        (form.value.qualify_score ?? 0) +
        (form.value.timeliness_score ?? 0)
}

const handleSave = () => {
    formRef.value?.validate((valid) => {
        if (!valid) return
        updateTotalScore()
        if (form.value.evaluation_id) {
            // 编辑
            const index = tableData.value.findIndex(item => item.evaluation_id === form.value.evaluation_id)
            if (index !== -1) {
                tableData.value[index] = form.value as SupplierEvaluation
            }
        } else {
            // 添加
            const newId = Date.now()
            tableData.value.push({ ...(form.value as SupplierEvaluation), evaluation_id: newId })
        }
        dialogVisible.value = false
    })
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.evaluation_id !== id)
    if (paginatedData.value.length === 0 && currentPage.value > 1) {
        currentPage.value--
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

// 表单验证规则
const rules = {
    supplier_id: [{ required: true, message: '请选择供应商', trigger: 'change' }],
    evaluator_id: [{ required: true, message: '请选择评价人员', trigger: 'change' }],
    evaluation_date: [{ required: true, message: '请选择评价时间', trigger: 'change' }],
    service_score: [{ required: true, type: 'number', message: '请选择服务评分', trigger: 'change' }],
    qualify_score: [{ required: true, type: 'number', message: '请选择供货质量评分', trigger: 'change' }],
    timeliness_score: [{ required: true, type: 'number', message: '请选择供货及时性评分', trigger: 'change' }],
    comment: [{ required: true, message: '请输入综合评价', trigger: 'blur' }],
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 16px;
}
</style>
