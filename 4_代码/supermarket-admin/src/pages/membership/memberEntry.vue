<template>
    <el-card>
        <div class="mb-4">
            <el-button type="primary" @click="openDialog()">新增会员</el-button>
        </div>

        <el-table :data="pagedData" border>
            <el-table-column prop="member_id" label="会员ID" width="80" />
            <el-table-column prop="name" label="姓名" />
            <el-table-column prop="gender" label="性别" width="80" :formatter="genderFormatter" />
            <el-table-column prop="birthday" label="生日" />
            <el-table-column prop="phone" label="手机号" />
            <el-table-column prop="registration_date" label="注册日期" />
            <el-table-column prop="level_name" label="会员等级" />
            <el-table-column prop="points" label="积分点数" width="80" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="deleteMember(scope.row.member_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <!-- 分页放这里 -->
        <div class="pagination-wrapper" style="margin-top: 20px; text-align: right;">
            <el-pagination layout="prev, pager, next" :page-size="pageSize" :total="total"
                @current-change="handlePageChange" />
        </div>

        <!-- 弹窗表单 -->
        <el-dialog :title="form.member_id ? '编辑会员' : '新增会员'" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="姓名">
                    <el-input v-model="form.name" />
                </el-form-item>
                <el-form-item label="性别">
                    <el-select v-model="form.gender" placeholder="请选择">
                        <el-option label="男" :value="0" />
                        <el-option label="女" :value="1" />
                    </el-select>
                </el-form-item>
                <el-form-item label="生日">
                    <el-date-picker v-model="form.birthday" type="date" placeholder="选择日期" />
                </el-form-item>
                <el-form-item label="手机号">
                    <el-input v-model="form.phone" />
                </el-form-item>
                <el-form-item label="注册日期">
                    <el-date-picker v-model="form.registration_date" type="date" placeholder="选择日期" />
                </el-form-item>
                <el-form-item label="会员等级">
                    <el-select v-model="form.level_id" placeholder="请选择会员等级">
                        <el-option v-for="level in memberLevels" :key="level.level_id" :label="level.level_name"
                            :value="level.level_id" />
                    </el-select>
                </el-form-item>
                <el-form-item label="积分">
                    <el-input-number v-model="form.points" :min="0" />
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
    member_id: number
    level_id: number
    name: string
    gender: number // 0男 1女
    birthday: string
    phone: string
    registration_date: string
    points: number
}

// 假会员等级数据
const memberLevels = ref([
    { level_id: 1, level_name: '普通会员' },
    { level_id: 2, level_name: '银卡会员' },
    { level_id: 3, level_name: '金卡会员' },
])

const pageSize = 10
const currentPage = ref(1)
const dialogVisible = ref(false)
const form = ref<Member>({
    member_id: 0,
    level_id: 1,
    name: '',
    gender: 0,
    birthday: '',
    phone: '',
    registration_date: '',
    points: 0,
})

// 生成假数据
const members = ref<Member[]>(
    Array.from({ length: 50 }, (_, i) => ({
        member_id: i + 1,
        level_id: (i % 3) + 1,
        name: `会员${i + 1}`,
        gender: i % 2 === 0 ? 0 : 1,
        birthday: `199${i % 10}-0${(i % 9) + 1}-15`,
        phone: `1380000${String(i).padStart(4, '0')}`,
        registration_date: `2023-0${(i % 9) + 1}-01`,
        points: Math.floor(Math.random() * 1000),
    }))
)

const total = computed(() => members.value.length)

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
            member_id: 0,
            level_id: 1,
            name: '',
            gender: 0,
            birthday: '',
            phone: '',
            registration_date: '',
            points: 0,
        }
    }
    dialogVisible.value = true
}

const save = () => {
    if (form.value.member_id) {
        const index = members.value.findIndex((m) => m.member_id === form.value.member_id)
        if (index !== -1) members.value[index] = { ...form.value }
    } else {
        form.value.member_id = members.value.length + 1
        members.value.unshift({ ...form.value })
    }
    dialogVisible.value = false
}

const deleteMember = (member_id: number) => {
    members.value = members.value.filter((m) => m.member_id !== member_id)
}

// 性别格式化显示
const genderFormatter = (row: Member) => (row.gender === 0 ? '男' : '女')
</script>

<style scoped>
.mb-4 {
    margin-bottom: 1rem;
}
</style>
