<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加积分政策</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="policyId" label="政策ID" width="100" />
            <el-table-column prop="policyName" label="政策名称" />
            <el-table-column prop="pointsPerYuan" label="每满1元获得积分" />
            <el-table-column prop="startDate" label="生效日期" />
            <el-table-column prop="endDate" label="失效日期" />
            <el-table-column prop="description" label="政策描述" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.policyId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="120px">
                <el-form-item label="政策名称">
                    <el-input v-model="form.policyName" placeholder="请输入政策名称" />
                </el-form-item>
                <el-form-item label="每满1元获积分">
                    <el-input v-model.number="form.pointsPerYuan" placeholder="例如：10" />
                </el-form-item>
                <el-form-item label="生效日期">
                    <el-date-picker v-model="form.startDate" type="date" placeholder="请选择生效日期" style="width: 100%" />
                </el-form-item>
                <el-form-item label="失效日期">
                    <el-date-picker v-model="form.endDate" type="date" placeholder="请选择失效日期" style="width: 100%" />
                </el-form-item>
                <el-form-item label="政策描述">
                    <el-input v-model="form.description" type="textarea" rows="3" placeholder="请输入政策描述" />
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

interface PointsPolicy {
    policyId: number
    policyName: string
    pointsPerYuan: number
    description: string
    startDate: string
    endDate: string
}

const generateFakeData = (): PointsPolicy[] => {
    return [
        {
            policyId: 1,
            policyName: '基础积分政策',
            pointsPerYuan: 10,
            description: '每消费1元获得10积分，有效期至2025年底',
            startDate: '2025-01-01',
            endDate: '2025-12-31',
        },
        {
            policyId: 2,
            policyName: '促销积分',
            pointsPerYuan: 20,
            description: '促销期间每1元获得20积分',
            startDate: '2025-06-01',
            endDate: '2025-06-30',
        },
    ]
}

const tableData = ref<PointsPolicy[]>(generateFakeData())

const dialogVisible = ref(false)
const dialogTitle = ref('添加积分政策')
const form = ref<Partial<PointsPolicy>>({})

const currentPage = ref(1)
const pageSize = ref(5)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: PointsPolicy) => {
    dialogTitle.value = row ? '编辑积分政策' : '添加积分政策'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.policyId) {
        const idx = tableData.value.findIndex(item => item.policyId === form.value.policyId)
        if (idx !== -1) {
            tableData.value[idx] = form.value as PointsPolicy
        }
    } else {
        const newId = tableData.value.length ? Math.max(...tableData.value.map(i => i.policyId)) + 1 : 1
        tableData.value.push({ ...(form.value as PointsPolicy), policyId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.policyId !== id)
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
