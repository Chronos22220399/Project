<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="记录ID" width="100" />
            <el-table-column prop="memberId" label="会员ID" />
            <el-table-column prop="redeemItemId" label="被兑换物品id">
                <template #default="scope">
                    {{ getItemName(scope.row.redeemItemId) }}
                </template>
            </el-table-column>
            <el-table-column prop="pointsUsed" label="消耗积分" />
            <el-table-column prop="operator" label="操作员" />
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
            <el-form :model="form">
                <el-form-item label="会员ID"><el-input v-model="form.memberId" /></el-form-item>
                <el-form-item label="兑换内容">
                    <el-select v-model="form.redeemItemId" placeholder="请选择">
                        <el-option v-for="item in items" :key="item.id" :label="item.name" :value="item.id" />
                    </el-select>
                </el-form-item>
                <el-form-item label="消耗积分"><el-input v-model="form.pointsUsed" /></el-form-item>
                <el-form-item label="操作员"><el-input v-model="form.operator" /></el-form-item>
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

interface RedeemRecord {
    id: number
    memberId: number
    redeemItemId: number
    pointsUsed: number
    operator: string
}

interface RedeemItem {
    id: number
    name: string
}

const generateFakeData = (): RedeemRecord[] => {
    return Array.from({ length: 50 }, (_, i) => ({
        id: i + 1,
        memberId: 1000 + i,
        redeemItemId: (i % 5) + 1,
        pointsUsed: Math.floor(Math.random() * 100) + 10,
        operator: `员工${(i % 3) + 1}`
    }))
}

const items: RedeemItem[] = [
    { id: 1, name: '毛巾' },
    { id: 2, name: '洗发水' },
    { id: 3, name: '购物券' },
    { id: 4, name: '积分卡' },
    { id: 5, name: '小电扇' }
]

const getItemName = (id: number) => {
    const item = items.find(i => i.id === id)
    return item ? item.name : '未知'
}

const tableData = ref<RedeemRecord[]>(generateFakeData())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加记录')
const form = ref<Partial<RedeemRecord>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: RedeemRecord) => {
    dialogTitle.value = row ? '编辑记录' : '添加记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.id) {
        const index = tableData.value.findIndex(r => r.id === form.value.id)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as RedeemRecord) }
        }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as RedeemRecord), id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.id !== id)
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
