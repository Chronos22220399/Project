<template>
    <el-card>
        <div class="flex justify-between items-center mb-4">
            <el-button type="primary" @click="openDialog()">新增会员</el-button>
            <el-pagination layout="prev, pager, next" :page-size="pageSize" :total="total"
                @current-change="handlePageChange" />
        </div>
        <el-table :data="pagedData" border>
            <el-table-column prop="id" label="会员ID" width="80" />
            <el-table-column prop="name" label="姓名" />
            <el-table-column prop="gender" label="性别" />
            <el-table-column prop="birthday" label="生日" />
            <el-table-column prop="phone" label="手机号" />
            <el-table-column prop="registrationDate" label="注册时间" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="deleteMember(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <!-- 弹窗表单 -->
        <el-dialog :title="form.id ? '编辑会员' : '新增会员'" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="姓名">
                    <el-input v-model="form.name" />
                </el-form-item>
                <el-form-item label="性别">
                    <el-select v-model="form.gender" placeholder="请选择">
                        <el-option label="男" value="男" />
                        <el-option label="女" value="女" />
                    </el-select>
                </el-form-item>
                <el-form-item label="生日">
                    <el-date-picker v-model="form.birthday" type="date" placeholder="选择日期" />
                </el-form-item>
                <el-form-item label="手机号">
                    <el-input v-model="form.phone" />
                </el-form-item>
                <el-form-item label="注册时间">
                    <el-date-picker v-model="form.registrationDate" type="date" placeholder="选择日期" />
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

interface Member {
    id: number
    name: string
    gender: string
    birthday: string
    phone: string
    registrationDate: string
}

const pageSize = 5
const currentPage = ref(1)
const dialogVisible = ref(false)
const form = ref<Member>({} as Member)

// 生成假数据
const members = ref<Member[]>(
    Array.from({ length: 50 }, (_, i) => ({
        id: i + 1,
        name: `会员${i + 1}`,
        gender: i % 2 === 0 ? '男' : '女',
        birthday: `199${i % 10}-0${(i % 9) + 1}-15`,
        phone: `1380000${String(i).padStart(4, '0')}`,
        registrationDate: `2023-0${(i % 9) + 1}-01`,
    }))
)

const total = members.value.length

const pagedData = computed(() =>
    members.value.slice((currentPage.value - 1) * pageSize, currentPage.value * pageSize)
)

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const openDialog = (member?: Member) => {
    if (member) {
        form.value = { ...member }
    } else {
        form.value = {
            id: 0,
            name: '',
            gender: '',
            birthday: '',
            phone: '',
            registrationDate: '',
        }
    }
    dialogVisible.value = true
}

const save = () => {
    if (form.value.id) {
        const index = members.value.findIndex((m) => m.id === form.value.id)
        if (index !== -1) members.value[index] = { ...form.value }
    } else {
        form.value.id = members.value.length + 1
        members.value.unshift({ ...form.value })
    }
    dialogVisible.value = false
}

const deleteMember = (id: number) => {
    members.value = members.value.filter((m) => m.id !== id)
}
</script>

<style scoped>
.mb-4 {
    margin-bottom: 1rem;
}
</style>
