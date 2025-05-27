<template>
    <el-container>
        <el-header>
            <el-button type="primary" @click="showCreateDialog">添加仓库</el-button>
        </el-header>
        <el-main>
            <el-table :data="warehouses" border style="width: 100%">
                <el-table-column prop="warehouse_id" label="仓库ID" width="100" />
                <el-table-column prop="warehouse_name" label="仓库名" />
                <el-table-column prop="location" label="地址" />
                <el-table-column prop="capacity" label="容量" />
                <el-table-column prop="phone" label="联系电话" />
                <el-table-column prop="manager_id" label="管理员ID" />
                <el-table-column prop="status" label="状态" />
                <el-table-column prop="remark" label="备注" />
                <el-table-column label="操作" width="180">
                    <template #default="scope">
                        <el-button size="small" @click="showUpdateDialog(scope.row)">更新</el-button>
                        <el-button size="small" type="danger"
                            @click="deleteWarehouse(scope.row.warehouse_id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <el-pagination :current-page="currentPage" :page-size="pageSize" :total="total"
                @current-change="handlePageChange" layout="prev, pager, next, jumper"
                style="margin-top: 20px; text-align: right;" />
        </el-main>

        <!-- 添加弹窗 -->
        <el-dialog v-model="createDialogVisible" title="添加仓库" width="500px">
            <el-form ref="createFormRef" :model="createForm" :rules="formRules" label-width="120px">
                <el-form-item label="仓库名" prop="warehouse_name">
                    <el-input v-model="createForm.warehouse_name" />
                </el-form-item>
                <el-form-item label="地址" prop="location">
                    <el-input v-model="createForm.location" />
                </el-form-item>
                <el-form-item label="容量" prop="capacity">
                    <el-input-number v-model="createForm.capacity" :min="0" />
                </el-form-item>

                <el-form-item label="经理ID" prop="manager_id">
                    <el-input v-model="createForm.manager_id" />
                </el-form-item>
                <el-form-item label="联系电话" prop="phone">
                    <el-input v-model="createForm.phone" />
                </el-form-item>
                <el-form-item label="状态" prop="status">
                    <el-select v-model="createForm.status" placeholder="请选择状态">
                        <el-option label="启用" value="active" />
                        <el-option label="停用" value="inactive" />
                        <el-option label="维护中" value="maintenance" />
                        <el-option label="已关闭" value="closed" />
                    </el-select>
                </el-form-item>
                <el-form-item label="备注" prop="remark">
                    <el-input type="textarea" v-model="createForm.remark" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="createDialogVisible = false">取消</el-button>
                <el-button type="primary" @click="createWarehouse">确认</el-button>
            </template>
        </el-dialog>

        <!-- 更新弹窗 -->
        <el-dialog v-model="updateDialogVisible" title="更新仓库" width="500px">
            <el-form ref="updateFormRef" :model="updateForm" :rules="formRules" label-width="120px">
                <el-form-item label="仓库名" prop="warehouse_name">
                    <el-input v-model="updateForm.warehouse_name" />
                </el-form-item>
                <el-form-item label="地址" prop="location">
                    <el-input v-model="updateForm.location" />
                </el-form-item>
                <el-form-item label="容量" prop="capacity">
                    <el-input-number v-model="updateForm.capacity" :min="0" />
                </el-form-item>

                <el-form-item label="经理ID" prop="manager_id">
                    <el-input v-model="updateForm.manager_id" />
                </el-form-item>
                <el-form-item label="联系电话" prop="phone">
                    <el-input v-model="updateForm.phone" />
                </el-form-item>
                <el-form-item label="状态" prop="status">
                    <el-select v-model="updateForm.status" placeholder="请选择状态">
                        <el-option label="启用" value="active" />
                        <el-option label="停用" value="inactive" />
                        <el-option label="维护中" value="maintenance" />
                        <el-option label="已关闭" value="closed" />
                    </el-select>
                </el-form-item>
                <el-form-item label="备注" prop="remark">
                    <el-input type="textarea" v-model="updateForm.remark" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="updateDialogVisible = false">取消</el-button>
                <el-button type="primary" @click="updateWarehouse">确认</el-button>
            </template>
        </el-dialog>
    </el-container>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted, toRaw } from 'vue'
import { ElMessage } from 'element-plus'
import axios from 'axios'

const API_BASE = '/api/warehouse'

interface Warehouse {
    warehouse_id: string
    warehouse_name: string
    location: string
    capacity: number
    manager_id: string
    phone: string
    status: string
    remark: string
}

const warehouses = ref<Warehouse[]>([])
const total = ref(0)
const currentPage = ref(1)
const pageSize = ref(10)

const createDialogVisible = ref(false)
const updateDialogVisible = ref(false)

const createForm = reactive<Warehouse>({
    warehouse_id: '',
    warehouse_name: '',
    location: '',
    capacity: 0,
    phone: '',
    manager_id: '',
    status: 'inactive',
    remark: '',
})

const updateForm = reactive<Warehouse>({
    warehouse_id: '',
    warehouse_name: '',
    location: '',
    capacity: 0,
    phone: '',
    manager_id: '',
    status: 'inactive',
    remark: '',
})

const createFormRef = ref()
const updateFormRef = ref()

const formRules = {
    warehouse_name: [{ required: true, message: '请输入仓库名', trigger: 'blur' }],
    location: [{ required: true, message: '请输入地址', trigger: 'blur' }],
    capacity: [{ required: true, type: 'number', message: '请输入容量', trigger: 'blur' }],
    phone: [{ required: true, message: '请输入联系电话', trigger: 'blur' }],
    manager_id: [{ required: true, message: '请输入管理员ID', trigger: 'blur' }],
    status: [
        { required: true, message: '请选择状态', trigger: 'change' },
        {
            validator: (_rule: any, value: string, callback: any) => {
                const validStatuses = ['active', 'inactive', 'maintenance', 'closed']
                if (!validStatuses.includes(value)) {
                    callback(new Error('状态值不正确'))
                } else {
                    callback()
                }
            },
            trigger: 'change',
        },
    ],
    remark: [],
}

const fetchWarehouses = async () => {
    try {
        const res = await axios.post(`${API_BASE}/get_by_page`, {
            page: currentPage.value,
            page_size: pageSize.value,
        })
        if (res.data?.code === 200 && Array.isArray(res.data.data?.items)) {
            warehouses.value = res.data.data.items
            total.value = res.data.data.total || 0
        } else {
            warehouses.value = []
            total.value = 0
            ElMessage.error('返回数据格式不正确')
        }
    } catch (err) {
        ElMessage.error('获取仓库数据失败')
        console.error(err)
    }
}

const showCreateDialog = () => {
    Object.assign(createForm, {
        warehouse_name: '',
        location: '',
        capacity: 0,
        phone: '',
        manager_id: '',
        status: 'inactive',
        remark: '',
    })
    createDialogVisible.value = true
}

const createWarehouse = () => {
    if (!createFormRef.value) return
        ; (createFormRef.value as any).validate(async (valid: boolean) => {
            if (!valid) return
            try {
                console.log('创建仓库时发送的数据:', JSON.stringify(createForm))

                await axios.post(`${API_BASE}/create`, toRaw(createForm))
                ElMessage.success('添加仓库成功')
                createDialogVisible.value = false
                await fetchWarehouses()
            } catch (err) {
                ElMessage.error('添加仓库失败')
                console.error(err)
            }
        })
}

const showUpdateDialog = (row: Warehouse) => {
    Object.assign(updateForm, row)
    updateDialogVisible.value = true
}

const updateWarehouse = () => {
    if (!updateFormRef.value) return
        ; (updateFormRef.value as any).validate(async (valid: boolean) => {
            if (!valid) return
            try {
                await axios.post(`${API_BASE}/update`, toRaw(updateForm))
                ElMessage.success('更新仓库成功')
                updateDialogVisible.value = false
                await fetchWarehouses()
            } catch (err) {
                ElMessage.error('更新仓库失败')
                console.error(err)
            }
        })
}

const deleteWarehouse = async (id: string) => {
    try {
        await axios.post(`${API_BASE}/remove`, { warehouse_id: id })
        ElMessage.success('删除仓库成功')
        await fetchWarehouses()
    } catch (err) {
        ElMessage.error('删除仓库失败')
        console.error(err)
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
    fetchWarehouses()
}

onMounted(() => {
    fetchWarehouses()
})
</script>
