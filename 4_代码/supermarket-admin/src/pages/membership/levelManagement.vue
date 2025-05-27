<template>
    <el-card>
        <div class="mb-4">
            <el-button type="primary" @click="openDialog()">新增等级</el-button>
        </div>

        <el-table :data="pagedData" border>
            <el-table-column prop="id" label="等级ID" width="80" />
            <el-table-column prop="name" label="等级名称" />
            <el-table-column prop="discount" label="折扣率(%)" width="120" />
            <el-table-column prop="pointsRequired" label="所需积分" width="100" />
            <el-table-column prop="status" label="状态" width="100">
                <template #default="{ row }">
                    <el-tag type="success" v-if="row.status === 1">有效</el-tag>
                    <el-tag type="info" v-else>无效</el-tag>
                </template>
            </el-table-column>
            <el-table-column prop="note" label="备注" />
            <el-table-column prop="createdAt" label="创建时间" width="180" />
            <el-table-column prop="updatedAt" label="更新时间" width="180" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="deleteLevel(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <!-- 分页组件 -->
        <div style="margin-top: 20px; text-align: right;">
            <el-pagination layout="prev, pager, next" :page-size="pageSize" :total="total"
                @current-change="handlePageChange" />
        </div>

        <!-- 弹窗表单 -->
        <el-dialog :title="form.id ? '编辑等级' : '新增等级'" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="100px" ref="formRef">
                <el-form-item label="等级名称" prop="name"
                    :rules="[{ required: true, message: '请输入等级名称', trigger: 'blur' }]">
                    <el-input v-model="form.name" autocomplete="off" />
                </el-form-item>
                <el-form-item label="折扣率 (%)" prop="discount"
                    :rules="[{ required: true, message: '请输入折扣率', trigger: 'blur' }]">
                    <el-input-number v-model="form.discount" :min="0" :max="100" controls-position="right" />
                </el-form-item>
                <el-form-item label="所需积分" prop="pointsRequired"
                    :rules="[{ required: true, message: '请输入所需积分', trigger: 'blur' }]">
                    <el-input-number v-model="form.pointsRequired" :min="0" controls-position="right" />
                </el-form-item>
                <el-form-item label="状态" prop="status">
                    <el-switch v-model="form.status" active-value="1" inactive-value="0" active-text="有效"
                        inactive-text="无效" />
                </el-form-item>
                <el-form-item label="备注">
                    <el-input v-model="form.note" type="textarea" rows="3" />
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
import { ElMessage, ElMessageBox } from 'element-plus'

interface Level {
    id: number
    name: string
    discount: number
    pointsRequired: number
    status: 1 | 0
    note: string
    createdAt: string
    updatedAt: string
}

const pageSize = 5
const currentPage = ref(1)
const dialogVisible = ref(false)
const formRef = ref()
const form = ref<Level>({
    id: 0,
    name: '',
    discount: 100,
    pointsRequired: 0,
    status: 1,
    note: '',
    createdAt: '',
    updatedAt: '',
})

const now = () => new Date().toISOString().slice(0, 19).replace('T', ' ')

const levels = ref<Level[]>(
    Array.from({ length: 50 }, (_, i) => ({
        id: i + 1,
        name: `等级${i + 1}`,
        discount: 100 - (i % 10) * 5,
        pointsRequired: (i + 1) * 100,
        status: i % 2 === 0 ? 1 : 0,
        note: `这是等级${i + 1}的备注`,
        createdAt: now(),
        updatedAt: now(),
    }))
)

const total = computed(() => levels.value.length)

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
            discount: 100,
            pointsRequired: 0,
            status: 1,
            note: '',
            createdAt: '',
            updatedAt: '',
        }
    }
    dialogVisible.value = true
}

const save = () => {
    // 简单表单验证
    if (!form.value.name) {
        ElMessage.error('等级名称不能为空')
        return
    }
    if (form.value.discount < 0 || form.value.discount > 100) {
        ElMessage.error('折扣率必须在0到100之间')
        return
    }
    if (form.value.pointsRequired < 0) {
        ElMessage.error('所需积分不能为负数')
        return
    }

    if (form.value.id) {
        const index = levels.value.findIndex((l) => l.id === form.value.id)
        if (index !== -1) {
            form.value.updatedAt = now()
            levels.value[index] = { ...form.value }
        }
    } else {
        form.value.id = levels.value.length ? Math.max(...levels.value.map(l => l.id)) + 1 : 1
        const dateNow = now()
        form.value.createdAt = dateNow
        form.value.updatedAt = dateNow
        levels.value.unshift({ ...form.value })
    }
    dialogVisible.value = false
    ElMessage.success('保存成功')
}

const deleteLevel = (id: number) => {
    ElMessageBox.confirm('确认删除该等级吗？', '提示', {
        type: 'warning',
    }).then(() => {
        levels.value = levels.value.filter((l) => l.id !== id)
        ElMessage.success('删除成功')
    }).catch(() => { })
}
</script>

<style scoped>
.mb-4 {
    margin-bottom: 1rem;
}
</style>
