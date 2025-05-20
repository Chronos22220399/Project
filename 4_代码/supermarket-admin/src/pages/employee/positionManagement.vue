<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加岗位</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="岗位ID" width="100" />
            <el-table-column prop="name" label="岗位名称" />
            <el-table-column prop="description" label="岗位描述" />
            <el-table-column prop="baseSalary" label="基础工资（元）" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="岗位名称"><el-input v-model="form.name" /></el-form-item>
                <el-form-item label="岗位描述"><el-input v-model="form.description" type="textarea" /></el-form-item>
                <el-form-item label="基础工资"><el-input-number v-model="form.baseSalary" :min="0" /></el-form-item>
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
import axios from 'axios'

interface JobPosition {
    id: number
    name: string
    description: string
    baseSalary: number
}

// 生成假数据
const generateFakePositions = (): JobPosition[] => {
    const titles = ['财务部门经理', '商品部门经理', '人事专员', '销售经理', '出纳', '产品经理', '仓库管理员']
    return Array.from({ length: 50 }, (_, i) => ({
        id: i + 1,
        name: titles[i % titles.length],
        description: `负责${titles[i % titles.length]}相关工作`,
        baseSalary: Math.floor(Math.random() * 5000 + 5000)
    }))
}

const tableData = ref<JobPosition[]>(generateFakePositions())
const dialogVisible = ref(false)
const dialogTitle = ref('添加岗位')
const form = ref<Partial<JobPosition>>({})

// 分页相关
const currentPage = ref(1)
const pageSize = ref(10)
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

// 打开弹窗
const openDialog = (row?: JobPosition) => {
    dialogTitle.value = row ? '编辑岗位' : '添加岗位'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

// 保存
const handleSave = async () => {
    const newData = { ...form.value }
    try {
        if (form.value.id) {
            await axios.put(`/api/job/${form.value.id}`, newData)
            const index = tableData.value.findIndex(job => job.id === form.value.id)
            if (index !== -1) tableData.value[index] = form.value as JobPosition
        } else {
            const response = await axios.post('/api/job', newData)
            const newId = response.data.id || Date.now()
            tableData.value.push({ ...(form.value as JobPosition), id: newId })
        }
        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

// 删除
const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/job/${id}`)
        tableData.value = tableData.value.filter(job => job.id !== id)
    } catch (err) {
        console.error('删除失败', err)
    }
}

// 翻页
const handlePageChange = (page: number) => {
    currentPage.value = page
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
