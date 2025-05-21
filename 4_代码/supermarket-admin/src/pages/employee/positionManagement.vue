<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加岗位</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="position_id" label="岗位ID" width="100" />
            <el-table-column prop="position_name" label="岗位名称" />
            <el-table-column prop="department" label="所属部门" />
            <el-table-column prop="description" label="岗位描述" />
            <el-table-column prop="base_salary" label="基础工资（元）" />
            <el-table-column label="是否管理岗" width="100">
                <template #default="scope">
                    <el-tag type="success" v-if="scope.row.is_manager">是</el-tag>
                    <el-tag type="info" v-else>否</el-tag>
                </template>
            </el-table-column>
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.position_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 20px;"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="岗位名称" required>
                    <el-input v-model="form.position_name" />
                </el-form-item>
                <el-form-item label="所属部门" required>
                    <el-input v-model="form.department" />
                </el-form-item>
                <el-form-item label="岗位描述">
                    <el-input type="textarea" rows="3" v-model="form.description" />
                </el-form-item>
                <el-form-item label="基础工资">
                    <el-input-number v-model="form.base_salary" :min="0" :step="100" />
                </el-form-item>
                <el-form-item label="是否管理岗">
                    <el-switch v-model="form.is_manager" active-text="是" inactive-text="否" />
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
import axios from 'axios'

interface Position {
    position_id: number
    position_name: string
    department: string
    description: string
    base_salary: number
    is_manager: boolean
}

// 生成假数据
const generateFakePositions = (): Position[] => {
    const titles = ['财务部门经理', '商品部门经理', '人事专员', '销售经理', '出纳', '产品经理', '仓库管理员']
    const departments = ['财务部', '商品部', '人事部', '销售部', '财务部', '产品部', '仓库部']
    return Array.from({ length: 50 }, (_, i) => ({
        position_id: i + 1,
        position_name: titles[i % titles.length],
        department: departments[i % departments.length],
        description: `负责${titles[i % titles.length]}相关工作`,
        base_salary: Math.floor(Math.random() * 5000 + 5000),
        is_manager: (i % 3) === 0 // 每三个里有一个是管理岗
    }))
}

const tableData = ref<Position[]>(generateFakePositions())
const dialogVisible = ref(false)
const dialogTitle = ref('添加岗位')
const form = ref<Partial<Position>>({})

// 分页相关
const currentPage = ref(1)
const pageSize = ref(10)
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

// 打开弹窗
const openDialog = (row?: Position) => {
    dialogTitle.value = row ? '编辑岗位' : '添加岗位'
    form.value = row ? { ...row } : {
        position_name: '',
        department: '',
        description: '',
        base_salary: 0,
        is_manager: false,
    }
    dialogVisible.value = true
}

// 保存
const handleSave = async () => {
    if (!form.value.position_name || !form.value.department) {
        alert('岗位名称和所属部门为必填项')
        return
    }

    try {
        if (form.value.position_id) {
            await axios.put(`/api/position/${form.value.position_id}`, form.value)
            const index = tableData.value.findIndex(pos => pos.position_id === form.value.position_id)
            if (index !== -1) tableData.value[index] = form.value as Position
        } else {
            const response = await axios.post('/api/position', form.value)
            const newId = response.data.position_id || Date.now()
            tableData.value.push({ ...(form.value as Position), position_id: newId })
        }
        dialogVisible.value = false
    } catch (err) {
        console.error('保存失败', err)
    }
}

// 删除
const handleDelete = async (id: number) => {
    try {
        await axios.delete(`/api/position/${id}`)
        tableData.value = tableData.value.filter(pos => pos.position_id !== id)
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
