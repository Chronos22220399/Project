<template>
    <el-card>
        <div class="flex justify-between items-center mb-4">
            <el-button type="primary" @click="openDialog()">新增等级</el-button>
            <el-pagination layout="prev, pager, next" :page-size="pageSize" :total="total"
                @current-change="handlePageChange" />
        </div>
        <el-table :data="pagedData" border>
            <el-table-column prop="id" label="等级ID" width="80" />
            <el-table-column prop="name" label="等级名称" />
            <el-table-column prop="discount" label="折扣率" />
            <el-table-column prop="pointsRequired" label="所需积分" />
            <el-table-column prop="note" label="备注" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="deleteLevel(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <!-- 弹窗表单 -->
        <el-dialog :title="form.id ? '编辑等级' : '新增等级'" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="等级名称">
                    <el-input v-model="form.name" />
                </el-form-item>
                <el-form-item label="折扣率">
                    <el-input v-model="form.discount" />
                </el-form-item>
                <el-form-item label="所需积分">
                    <el-input v-model="form.pointsRequired" type="number" />
                </el-form-item>
                <el-form-item label="备注">
                    <el-input v-model="form.note" type="textarea" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="save">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script lang="ts" setup>
import { ref, computed } from 'vue'

interface Level {
    id: number
    name: string
    discount: string
    pointsRequired: number
    note: string
}

const pageSize = 5
const currentPage = ref(1)
const dialogVisible = ref(false)
const form = ref < Level > ({} as Level)

const levels = ref < Level[] > (
    Array.from({ length: 50 }, (_, i) => ({
        id: i + 1,
        name: `等级${i + 1}`,
        discount: `${(100 - i % 10 * 5)}%`,
        pointsRequired: (i + 1) * 100,
        note: `这是等级${i + 1}的备注`,
    }))
)

const total = levels.value.length

const pagedData = computed(() =>
    levels.value.slice((currentPage.value - 1) * pageSize, currentPage.value * pageSize)
)

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const openDialog = (level?: Level) => {
    if (level) {
        form.value = { ...level }
    } else {
        form.value = {
            id: 0,
            name: '',
            discount: '',
            pointsRequired: 0,
            note: '',
        }
    }
    dialogVisible.value = true
}

const save = () => {
    if (form.value.id) {
        const index = levels.value.findIndex((l) => l.id === form.value.id)
        if (index !== -1) levels.value[index] = { ...form.value }
    } else {
        form.value.id = levels.value.length + 1
        levels.value.unshift({ ...form.value })
    }
    dialogVisible.value = false
}

const deleteLevel = (id: number) => {
    levels.value = levels.value.filter((l) => l.id !== id)
}
</script>

<style scoped>
.mb-4 {
    margin-bottom: 1rem;
}
</style>
