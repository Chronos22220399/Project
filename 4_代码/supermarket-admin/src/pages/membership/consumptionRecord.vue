<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加消费记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="consumeId" label="消费ID" width="100" />
            <el-table-column prop="memberId" label="会员ID" width="100" />
            <el-table-column prop="memberName" label="会员姓名" />
            <el-table-column prop="amount" label="消费金额" />
            <el-table-column prop="consumeDate" label="消费时间" />
            <el-table-column prop="paymentMethod" label="消费方式" />
            <el-table-column prop="points" label="获得点数" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.consumeId)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form" label-width="100px">
                <el-form-item label="会员ID">
                    <el-input v-model="form.memberId" />
                </el-form-item>
                <el-form-item label="会员姓名">
                    <el-input v-model="form.memberName" />
                </el-form-item>
                <el-form-item label="消费金额">
                    <el-input v-model.number="form.amount" @input="updatePoints" />
                </el-form-item>
                <el-form-item label="获得点数">
                    <el-input :model-value="form.points" disabled />
                </el-form-item>
                <el-form-item label="消费时间">
                    <el-date-picker v-model="form.consumeDate" type="datetime" placeholder="选择日期时间"
                        style="width: 100%;" />
                </el-form-item>
                <el-form-item label="消费方式">
                    <el-select v-model="form.paymentMethod" placeholder="选择消费方式">
                        <el-option label="现金" value="现金" />
                        <el-option label="刷卡" value="刷卡" />
                        <el-option label="微信" value="微信" />
                        <el-option label="支付宝" value="支付宝" />
                        <el-option label="其他" value="其他" />
                    </el-select>
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
import { ref, computed, } from 'vue'

interface ConsumeRecord {
    consumeId: number
    memberId: number
    memberName: string
    amount: number
    consumeDate: string
    paymentMethod: string
    points: number
}

const POINTS_RATE = 0.05 // 1%消费金额转换为获得点数

const generateFakeData = (): ConsumeRecord[] => {
    return Array.from({ length: 50 }, (_, i) => {
        const amount = parseFloat((Math.random() * 500).toFixed(2))
        return {
            consumeId: i + 1,
            memberId: i + 1000,
            memberName: `会员${i + 1}`,
            amount,
            consumeDate: new Date(
                Date.now() - Math.floor(Math.random() * 10000000000)
            ).toISOString().slice(0, 19).replace('T', ' '),
            paymentMethod: ['现金', '刷卡', '微信', '支付宝', '其他'][i % 5],
            points: Math.floor(amount * POINTS_RATE),
        }
    })
}

const tableData = ref<ConsumeRecord[]>(generateFakeData())

const dialogVisible = ref(false)
const dialogTitle = ref('添加消费记录')
const form = ref<Partial<ConsumeRecord>>({})

const currentPage = ref(1)
const pageSize = ref(5)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

// 监听金额输入，自动计算获得点数
const updatePoints = () => {
    if (form.value.amount != null) {
        form.value.points = Math.floor(form.value.amount * POINTS_RATE)
    } else {
        form.value.points = 0
    }
}

const openDialog = (row?: ConsumeRecord) => {
    dialogTitle.value = row ? '编辑消费记录' : '添加消费记录'
    form.value = row ? { ...row } : { points: 0 }
    updatePoints()
    dialogVisible.value = true
}

const handleSave = () => {
    if (!form.value.amount) form.value.amount = 0
    updatePoints()

    if (form.value.consumeId) {
        const idx = tableData.value.findIndex((item) => item.consumeId === form.value.consumeId)
        if (idx !== -1) {
            tableData.value[idx] = { ...(form.value as ConsumeRecord) }
        }
    } else {
        const newId = tableData.value.length ? Math.max(...tableData.value.map(i => i.consumeId)) + 1 : 1
        tableData.value.push({ ...(form.value as ConsumeRecord), consumeId: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.consumeId !== id)
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
