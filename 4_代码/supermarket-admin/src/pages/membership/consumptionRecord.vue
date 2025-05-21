<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加消费记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="消费记录ID" width="120" />
            <el-table-column prop="member_id" label="会员ID" width="120" />
            <el-table-column prop="transaction_date" label="消费日期" />
            <el-table-column prop="amount" label="金额" />
            <el-table-column prop="earned_points" label="获得点数" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="120px">
                <el-form-item label="会员ID">
                    <el-input v-model.number="form.member_id" />
                </el-form-item>
                <el-form-item label="消费日期">
                    <el-date-picker v-model="form.transaction_date" type="datetime" placeholder="选择消费日期时间"
                        style="width: 100%" />
                </el-form-item>
                <el-form-item label="金额">
                    <el-input v-model.number="form.amount" @input="updatePoints" />
                </el-form-item>
                <el-form-item label="获得点数">
                    <el-input :model-value="form.earned_points" disabled />
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

interface MemberPurchaseRecord {
    id: number
    member_id: number
    transaction_date: string
    amount: number
    earned_points: number
}

const POINTS_RATE = 0.05 // 假设消费1元得5%的积分，具体规则后端调整

const generateFakeData = (): MemberPurchaseRecord[] => {
    return Array.from({ length: 50 }, (_, i) => {
        const amount = parseFloat((Math.random() * 500).toFixed(2))
        return {
            id: i + 1,
            member_id: i + 1000,
            transaction_date: new Date(
                Date.now() - Math.floor(Math.random() * 10000000000)
            ).toISOString().slice(0, 19).replace('T', ' '),
            amount,
            earned_points: Math.floor(amount * POINTS_RATE),
        }
    })
}

const tableData = ref<MemberPurchaseRecord[]>(generateFakeData())

const dialogVisible = ref(false)
const dialogTitle = ref('添加消费记录')
const form = ref<Partial<MemberPurchaseRecord>>({})

const currentPage = ref(1)
const pageSize = ref(5)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const updatePoints = () => {
    if (form.value.amount != null) {
        form.value.earned_points = Math.floor(form.value.amount * POINTS_RATE)
    } else {
        form.value.earned_points = 0
    }
}

const openDialog = (row?: MemberPurchaseRecord) => {
    dialogTitle.value = row ? '编辑消费记录' : '添加消费记录'
    form.value = row ? { ...row } : { earned_points: 0 }
    updatePoints()
    dialogVisible.value = true
}

const handleSave = () => {
    if (!form.value.amount) form.value.amount = 0
    updatePoints()

    if (form.value.id) {
        const idx = tableData.value.findIndex((item) => item.id === form.value.id)
        if (idx !== -1) {
            tableData.value[idx] = { ...(form.value as MemberPurchaseRecord) }
        }
    } else {
        const newId = tableData.value.length
            ? Math.max(...tableData.value.map((i) => i.id)) + 1
            : 1
        tableData.value.push({ ...(form.value as MemberPurchaseRecord), id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter((item) => item.id !== id)
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
