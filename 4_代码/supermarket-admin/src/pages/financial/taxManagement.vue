<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加税务记录</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="record_id" label="税务记录ID" width="150" />
            <el-table-column prop="tax_type" label="税种类型" width="120" />
            <el-table-column prop="tax_period" label="报税周期" width="140" />
            <el-table-column prop="tax_payable" label="应缴税金额" width="120" />
            <el-table-column prop="tax_paid" label="实缴税金额" width="120" />
            <el-table-column prop="paid_at" label="缴税时间" width="140" />
            <el-table-column prop="report_id" label="关联报表ID" width="120" />
            <el-table-column prop="declared_by" label="申报人ID" width="120" />
            <el-table-column prop="status" label="税务状态" width="120" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.record_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="税务记录ID">
                    <el-input v-model="form.record_id" :disabled="!!form.record_id" />
                </el-form-item>
                <el-form-item label="税种类型">
                    <el-input v-model="form.tax_type" />
                </el-form-item>
                <el-form-item label="报税周期">
                    <el-date-picker v-model="form.tax_period" type="month" placeholder="选择报税周期" />
                </el-form-item>
                <el-form-item label="应缴税金额">
                    <el-input-number v-model="form.tax_payable" :min="0" />
                </el-form-item>
                <el-form-item label="实缴税金额">
                    <el-input-number v-model="form.tax_paid" :min="0" />
                </el-form-item>
                <el-form-item label="缴税时间">
                    <el-date-picker v-model="form.paid_at" type="date" placeholder="选择缴税时间" />
                </el-form-item>
                <el-form-item label="关联报表ID">
                    <el-input v-model="form.report_id" />
                </el-form-item>
                <el-form-item label="申报人ID">
                    <el-input v-model="form.declared_by" />
                </el-form-item>
                <el-form-item label="税务状态">
                    <el-select v-model="form.status" placeholder="选择状态">
                        <el-option label="已申报" value="已申报" />
                        <el-option label="待申报" value="待申报" />
                        <el-option label="已缴清" value="已缴清" />
                        <el-option label="逾期未缴" value="逾期未缴" />
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
import { ref, computed } from 'vue'

interface TaxRecord {
    record_id: number | string
    tax_type: string
    tax_period: string
    tax_payable: number
    tax_paid: number
    paid_at: string
    report_id?: string | null
    declared_by: string
    status: string
}

const generateFakeTaxRecords = (): TaxRecord[] => [
    {
        record_id: 1,
        tax_type: '增值税',
        tax_period: '2025-04',
        tax_payable: 5000,
        tax_paid: 5000,
        paid_at: '2025-04-25',
        report_id: 'RPT1001',
        declared_by: '张三',
        status: '已缴清'
    },
    {
        record_id: 2,
        tax_type: '所得税',
        tax_period: '2025-04',
        tax_payable: 7000,
        tax_paid: 6000,
        paid_at: '2025-04-28',
        report_id: 'RPT1002',
        declared_by: '李四',
        status: '逾期未缴'
    }
]

const tableData = ref<TaxRecord[]>(generateFakeTaxRecords())
const currentPage = ref(1)
const pageSize = ref(5)
const dialogVisible = ref(false)
const dialogTitle = ref('添加税务记录')
const form = ref<Partial<TaxRecord>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: TaxRecord) => {
    dialogTitle.value = row ? '编辑税务记录' : '添加税务记录'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.record_id) {
        const index = tableData.value.findIndex(item => item.record_id === form.value.record_id)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as TaxRecord) }
        }
    } else {
        // 新增时自动生成一个唯一ID (简单模拟)
        const newId = Date.now()
        tableData.value.push({ ...(form.value as TaxRecord), record_id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (record_id: number | string) => {
    tableData.value = tableData.value.filter(item => item.record_id !== record_id)
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
