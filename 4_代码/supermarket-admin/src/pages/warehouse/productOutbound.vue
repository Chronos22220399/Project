<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加出库单</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="stock_out_id" label="出库单ID" width="120" />
            <el-table-column prop="warehouse_id" label="仓库ID" />
            <el-table-column prop="created_at" label="创建时间" />
            <el-table-column prop="created_by" label="创建人ID" />
            <el-table-column prop="destination_type" label="去向类型" />
            <el-table-column prop="destination_reference" label="去向编号" />
            <el-table-column prop="status" label="状态" />
            <el-table-column prop="remark" label="备注" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.stock_out_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <!-- 出库单弹窗 -->
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

                <el-form-item label="去向类型" prop="destination_type">
                    <el-select v-model="form.destination_type" placeholder="选择去向类型">
                        <el-option label="销售" value="销售" />
                        <el-option label="调拨" value="调拨" />
                        <el-option label="退货" value="退货" />
                        <el-option label="其他" value="其他" />
                    </el-select>
                </el-form-item>

                <el-form-item label="去向编号" prop="destination_reference">
                    <el-input v-model="form.destination_reference" autocomplete="off" />
                </el-form-item>

                <el-form-item label="状态" prop="status">
                    <el-select v-model="form.status" placeholder="选择状态">
                        <el-option label="待出库" value="待出库" />
                        <el-option label="已完成" value="已完成" />
                        <el-option label="已取消" value="已取消" />
                    </el-select>
                </el-form-item>

                <el-form-item label="备注" prop="remark">
                    <el-input type="textarea" v-model="form.remark" autocomplete="off" />
                </el-form-item>

                <el-divider>出库明细</el-divider>

                <!-- 使用子组件 -->
                <StockOutItems v-model="form.items" />
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
import StockOutItems from './StockOutItems.vue'

interface StockOutItem {
    item_id: number
    goods_id: string
    quantity: number
    price: number
    remark: string
}

interface StockOutOrder {
    stock_out_id: number
    warehouse_id: string
    created_at: string
    created_by: string
    destination_type: string
    destination_reference: string
    status: string
    remark: string
    items: StockOutItem[]
}

// 模拟假数据
const generateFakeItems = (stock_out_id: number): StockOutItem[] => {
    const count = Math.floor(Math.random() * 3) + 1
    return Array.from({ length: count }, (_, idx) => ({
        item_id: Date.now() + idx,
        goods_id: `G${idx + 1}`,
        quantity: Math.floor(Math.random() * 100) + 1,
        price: +(Math.random() * 100).toFixed(2),
        remark: `备注${idx + 1}`,
    }))
}

const generateFakeData = (): StockOutOrder[] => {
    return Array.from({ length: 50 }, (_, index) => {
        const id = index + 1
        return {
            stock_out_id: id,
            warehouse_id: `W${(index % 5) + 1}`,
            created_at: `2023-06-${String((index % 28) + 1).padStart(2, '0')} 10:00:00`,
            created_by: `U${(index % 10) + 1}`,
            destination_type: ['销售', '调拨', '退货', '其他'][index % 4],
            destination_reference: `REF-${2000 + index}`,
            status: ['待出库', '已完成', '已取消'][index % 3],
            remark: `备注${index + 1}`,
            items: generateFakeItems(id),
        }
    })
}

const tableData = ref<StockOutOrder[]>(generateFakeData())
const dialogVisible = ref(false)
const dialogTitle = ref('添加出库单')

const form = reactive<StockOutOrder>({
    stock_out_id: 0,
    warehouse_id: '',
    created_at: '',
    created_by: '',
    destination_type: '',
    destination_reference: '',
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
    destination_type: [{ required: true, message: '请选择去向类型', trigger: 'change' }],
    destination_reference: [{ required: true, message: '去向编号不能为空', trigger: 'blur' }],
    status: [{ required: true, message: '请选择状态', trigger: 'change' }],
}

// 打开弹窗 新增/编辑
const openDialog = (row?: StockOutOrder) => {
    dialogTitle.value = row ? '编辑出库单' : '添加出库单'
    if (row) {
        Object.assign(form, JSON.parse(JSON.stringify(row)))
    } else {
        Object.assign(form, {
            stock_out_id: 0,
            warehouse_id: '',
            created_at: '',
            created_by: '',
            destination_type: '',
            destination_reference: '',
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
    tableData.value = tableData.value.filter(item => item.stock_out_id !== id)
    ElMessage.success('删除成功')
}

// 保存
const handleSave = () => {
    mainFormRef.value?.validate(valid => {
        if (!valid) {
            ElMessage.error('请检查必填项！')
            return
        }
        if (form.stock_out_id === 0) {
            // 新增
            form.stock_out_id = Date.now()
            tableData.value.unshift(JSON.parse(JSON.stringify(form)))
        } else {
            // 更新
            const index = tableData.value.findIndex(item => item.stock_out_id === form.stock_out_id)
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
