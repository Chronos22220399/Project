<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加财务报表</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="report_id" label="报表ID" width="100" />
            <el-table-column prop="generated_by" label="生成人员ID" />
            <el-table-column prop="report_name" label="报表名称" />
            <el-table-column prop="report_type" label="报表类型" />
            <el-table-column prop="generated_at" label="生成时间" />
            <el-table-column prop="report_start_date" label="开始日期" />
            <el-table-column prop="report_end_date" label="结束日期" />
            <el-table-column prop="file_path" label="文件路径" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.report_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible">
            <el-form :model="form">
                <el-form-item label="生成人员ID"><el-input v-model="form.generated_by" /></el-form-item>
                <el-form-item label="报表名称"><el-input v-model="form.report_name" /></el-form-item>
                <el-form-item label="报表类型">
                    <el-select v-model="form.report_type" placeholder="选择类型">
                        <el-option label="日报" value="日报" />
                        <el-option label="周报" value="周报" />
                        <el-option label="月报" value="月报" />
                        <el-option label="年报" value="年报" />
                    </el-select>
                </el-form-item>
                <el-form-item label="生成时间">
                    <el-date-picker v-model="form.generated_at" type="datetime" />
                </el-form-item>
                <el-form-item label="开始日期">
                    <el-date-picker v-model="form.report_start_date" type="date" />
                </el-form-item>
                <el-form-item label="结束日期">
                    <el-date-picker v-model="form.report_end_date" type="date" />
                </el-form-item>
                <el-form-item label="文件路径"><el-input v-model="form.file_path" /></el-form-item>
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

interface FinancialReport {
    report_id: number
    generated_by: number
    report_name: string
    report_type: string
    generated_at: string
    report_start_date: string
    report_end_date: string
    file_path: string
}

// 假数据生成
const generateFakeReports = (): FinancialReport[] => {
    return Array.from({ length: 20 }, (_, i) => ({
        report_id: i + 1,
        generated_by: 100 + i,
        report_name: `财务报表-${i + 1}`,
        report_type: ['日报', '周报', '月报', '年报'][i % 4],
        generated_at: '2025-05-20 10:00:00',
        report_start_date: '2025-05-01',
        report_end_date: '2025-05-15',
        file_path: `/reports/report-${i + 1}.pdf`
    }))
}

const tableData = ref<FinancialReport[]>(generateFakeReports())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加财务报表')
const form = ref<Partial<FinancialReport>>({})

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: FinancialReport) => {
    dialogTitle.value = row ? '编辑财务报表' : '添加财务报表'
    form.value = row ? { ...row } : {}
    dialogVisible.value = true
}

const handleSave = () => {
    if (form.value.report_id) {
        const index = tableData.value.findIndex(item => item.report_id === form.value.report_id)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as FinancialReport) }
        }
    } else {
        const newId = Date.now()
        tableData.value.push({ ...(form.value as FinancialReport), report_id: newId })
    }
    dialogVisible.value = false
}

const handleDelete = (report_id: number) => {
    tableData.value = tableData.value.filter(item => item.report_id !== report_id)
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
