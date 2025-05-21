<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加入库单</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="stock_in_id" label="入库单ID" width="120" />
            <el-table-column prop="warehouse_id" label="仓库ID" />
            <el-table-column prop="created_at" label="创建时间" />
            <el-table-column prop="created_by" label="创建人ID" />
            <el-table-column prop="source_type" label="来源类型" />
            <el-table-column prop="source_reference" label="来源编号" />
            <el-table-column prop="status" label="状态" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.stock_in_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="900px" :close-on-click-modal="false">
            <el-form :model="form" label-width="110px" ref="mainFormRef" :rules="rules" status-icon>
                <el-form-item label="仓库ID" prop="warehouse_id">
                    <el-input v-model="form.warehouse_id" autocomplete="off" />
                </el-form-item>

                <el-form-item label="创建时间" prop="created_at">
                    <el-date-picker v-model="form.created_at" type="datetime" placeholder="选择日期时间"
                        style="width: 100%;" />
                </el-form-item>

                <el-form-item label="创建人ID" prop="created_by">
                    <el-input v-model="form.created_by" autocomplete="off" />
                </el-form-item>

                <el-form-item label="来源类型" prop="source_type">
                    <el-select v-model="form.source_type" placeholder="选择来源类型">
                        <el-option label="采购" value="采购" />
                        <el-option label="退货" value="退货" />
                        <el-option label="其他" value="其他" />
                    </el-select>
                </el-form-item>

                <el-form-item label="来源编号" prop="source_reference">
                    <el-input v-model="form.source_reference" autocomplete="off" />
                </el-form-item>

                <el-form-item label="状态" prop="status">
                    <el-select v-model="form.status" placeholder="选择状态">
                        <el-option label="待入库" value="待入库" />
                        <el-option label="已完成" value="已完成" />
                        <el-option label="已取消" value="已取消" />
                    </el-select>
                </el-form-item>

                <el-form-item label="备注" prop="remark">
                    <el-input type="textarea" v-model="form.remark" autocomplete="off" />
                </el-form-item>

                <el-divider>入库明细</el-divider>

                <StockInItems v-model="form.items" />
            </el-form>

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSave">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, reactive, computed } from 'vue'
import { ElMessage, type FormInstance } from 'element-plus'
import StockInItems from './StockInItems.vue'

interface StockInItem {
    item_id: number
    goods_id: string
    quantity: number
    remark: string
}

interface StockInOrder {
    stock_in_id: number
    warehouse_id: string
    created_at: string
    created_by: string
    source_type: string
    source_reference: string
    status: string
    remark: string
    items: StockInItem[]
}

const generateFakeItems = (stock_in_id: number): StockInItem[] => {
    const count = Math.floor(Math.random() * 3) + 1
    return Array.from({ length: count }, (_, idx) => ({
        item_id: Date.now() + idx,
        goods_id: `G${idx + 1}`,
        quantity: Math.floor(Math.random() * 100) + 1,
        remark: `备注${idx + 1}`,
    }))
}

const generateFakeData = (): StockInOrder[] => {
    return Array.from({ length: 50 }, (_, index) => {
        const id = index + 1
        return {
            stock_in_id: id,
            warehouse_id: `W${(index % 5) + 1}`,
            created_at: `2023-06-${String((index % 28) + 1).padStart(2, '0')} 10:00:00`,
            created_by: `U${(index % 10) + 1}`,
            source_type: ['采购', '退货', '其他'][index % 3],
            source_reference: `REF-${2000 + index}`,
            status: ['待入库', '已完成', '已取消'][index % 3],
            remark: `备注${index + 1}`,
            items: generateFakeItems(id),
        }
    })
}

const tableData = ref<StockInOrder[]>(generateFakeData())
const dialogVisible = ref(false)
const dialogTitle = ref('添加入库单')

const form = reactive<StockInOrder>({
    stock_in_id: 0,
    warehouse_id: '',
    created_at: '',
    created_by: '',
    source_type: '',
    source_reference: '',
    status: '',
    remark: '',
    items: [],
})

const currentPage = ref(1)
const pageSize = ref(10)
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const mainFormRef = ref<FormInstance>()

const rules = {
    warehouse_id: [{ required: true, message: '仓库ID不能为空', trigger: 'blur' }],
    created_at: [{ required: true, message: '创建时间不能为空', trigger: 'change' }],
    created_by: [{ required: true, message: '创建人ID不能为空', trigger: 'blur' }],
    source_type: [{ required: true, message: '请选择来源类型', trigger: 'change' }],
    source_reference: [{ required: true, message: '来源编号不能为空', trigger: 'blur' }],
    status: [{ required: true, message: '请选择状态', trigger: 'change' }],
}

const openDialog = (row?: StockInOrder) => {
    dialogTitle.value = row ? '编辑入库单' : '添加入库单'
    if (row) {
        Object.assign(form, JSON.parse(JSON.stringify(row)))
    } else {
        Object.assign(form, {
            stock_in_id: 0,
            warehouse_id: '',
            created_at: '',
            created_by: '',
            source_type: '',
            source_reference: '',
            status: '',
            remark: '',
            items: [],
        })
    }
    dialogVisible.value = true
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.stock_in_id !== id)
    ElMessage.success('删除成功')
}

const handleSave = () => {
    mainFormRef.value?.validate((valid) => {
        if (!valid) return
        if (form.stock_in_id === 0) {
            form.stock_in_id = Date.now()
            tableData.value.unshift(JSON.parse(JSON.stringify(form)))
        } else {
            const index = tableData.value.findIndex(item => item.stock_in_id === form.stock_in_id)
            if (index !== -1) {
                tableData.value[index] = JSON.parse(JSON.stringify(form))
            }
        }
        dialogVisible.value = false
        ElMessage.success('保存成功')
    })
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
