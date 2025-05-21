<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加积分政策</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="policy_id" label="积分政策ID" width="120" />
            <el-table-column prop="name" label="积分政策名称" />
            <el-table-column prop="point_per_yuan" label="满1元所得积分点数" />
            <el-table-column prop="effective_from" label="生效日期" />
            <el-table-column prop="effective_to" label="失效日期" />
            <el-table-column prop="description" label="积分政策描述" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.policy_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="140px">
                <el-form-item label="积分政策名称">
                    <el-input v-model="form.name" placeholder="请输入积分政策名称" />
                </el-form-item>
                <el-form-item label="满1元所得积分点数">
                    <el-input v-model.number="form.point_per_yuan" placeholder="例如：10" />
                </el-form-item>
                <el-form-item label="生效日期">
                    <el-date-picker v-model="form.effective_from" type="date" placeholder="请选择生效日期"
                        style="width: 100%" />
                </el-form-item>
                <el-form-item label="失效日期">
                    <el-date-picker v-model="form.effective_to" type="date" placeholder="请选择失效日期" style="width: 100%" />
                </el-form-item>
                <el-form-item label="积分政策描述">
                    <el-input v-model="form.description" type="textarea" rows="3" placeholder="请输入积分政策描述" />
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
    policy_id: number
    name: string
    point_per_yuan: number
    description: string
    effective_from: string
    effective_to: string
}

const generateFakeData = (): PointsPolicy[] => [
    {
        policy_id: 1,
        name: '基础积分政策',
        point_per_yuan: 10,
        description: '每消费1元获得10积分，有效期至2025年底',
        effective_from: '2025-01-01',
        effective_to: '2025-12-31',
    },
    {
        policy_id: 2,
        name: '促销积分',
        point_per_yuan: 20,
        description: '促销期间每1元获得20积分',
        effective_from: '2025-06-01',
        effective_to: '2025-06-30',
    },
]

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
    if (form.value.policy_id) {
        const idx = tableData.value.findIndex((item) => item.policy_id === form.value.policy_id)
        if (idx !== -1) {
            tableData.value[idx] = form.value as PointsPolicy
        }
    } else {
        const newId = tableData.value.length
            ? Math.max(...tableData.value.map((i) => i.policy_id)) + 1
            : 1
        tableData.value.push({ ...(form.value as PointsPolicy), policy_id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter((item) => item.policy_id !== id)
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
