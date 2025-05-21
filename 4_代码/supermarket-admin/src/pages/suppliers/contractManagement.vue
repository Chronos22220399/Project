<template>
    <el-card>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加合同</el-button>
        </div>
        <el-table :data="paginatedData" border style="width: 100%" :row-key="row => row.contract_id">
            <el-table-column prop="contract_id" label="合同ID" width="100" />
            <el-table-column prop="supplier_id" label="供应商ID" width="100" />
            <el-table-column prop="start_date" label="开始时间" />
            <el-table-column prop="end_date" label="结束时间" />
            <el-table-column prop="contract_amount" label="合同金额" />
            <el-table-column prop="status" label="合同状态" />
            <el-table-column prop="file_path" label="附件路径">
                <template #default="{ row }">
                    <a v-if="row.file_path" :href="row.file_path" target="_blank">{{ row.file_path }}</a>
                    <span v-else>无附件</span>
                </template>
            </el-table-column>
            <el-table-column label="操作" width="180" align="center">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="confirmDelete(scope.row.contract_id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
            style="margin-top: 10px" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="600px" @close="resetForm">
            <el-form :model="form" :rules="rules" ref="formRef" label-width="130px" status-icon>
                <el-form-item label="供应商ID" prop="supplier_id" required>
                    <el-input v-model="form.supplier_id" autocomplete="off" />
                </el-form-item>
                <el-form-item label="合同开始时间" prop="start_date" required>
                    <el-date-picker v-model="form.start_date" type="date" placeholder="选择开始时间" style="width: 100%;" />
                </el-form-item>
                <el-form-item label="合同结束时间" prop="end_date" required>
                    <el-date-picker v-model="form.end_date" type="date" placeholder="选择结束时间" style="width: 100%;" />
                </el-form-item>
                <el-form-item label="合同金额" prop="contract_amount" required>
                    <el-input-number v-model="form.contract_amount" :min="0" style="width: 100%;" />
                </el-form-item>
                <el-form-item label="合同状态" prop="status" required>
                    <el-select v-model="form.status" placeholder="请选择合同状态">
                        <el-option label="生效中" value="生效中" />
                        <el-option label="已过期" value="已过期" />
                        <el-option label="已终止" value="已终止" />
                    </el-select>
                </el-form-item>
                <el-form-item label="合同附件" prop="file_path">
                    <el-upload class="upload-demo" drag action="https://jsonplaceholder.typicode.com/posts/"
                        :on-success="handleUploadSuccess" :file-list="fileList" :auto-upload="true" :limit="1"
                        :on-remove="handleRemove" :before-upload="beforeUpload" :disabled="uploading">
                        <i class="el-icon-upload"></i>
                        <div class="el-upload__text">
                            将文件拖到此处，或<em>点击上传</em>
                        </div>
                        <div class="el-upload__tip" slot="tip">只能上传pdf/doc/docx格式，且不超过5MB</div>
                    </el-upload>
                    <div v-if="form.file_path" style="margin-top: 6px;">
                        当前文件路径：
                        <a :href="form.file_path" target="_blank">{{ form.file_path }}</a>
                    </div>
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="submitForm" :loading="uploading">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'
import type { FormInstance } from 'element-plus'

interface SupplierContract {
    contract_id: number
    supplier_id: number
    start_date: string
    end_date: string
    contract_amount: number
    status: string
    file_path?: string
}

const generateFakeContracts = (): SupplierContract[] => {
    return Array.from({ length: 15 }, (_, i) => ({
        contract_id: i + 1,
        supplier_id: (i % 10) + 1,
        start_date: `2024-01-${(i + 1).toString().padStart(2, '0')}`,
        end_date: `2025-01-${(i + 1).toString().padStart(2, '0')}`,
        contract_amount: 10000 + i * 500,
        status: ['生效中', '已过期', '已终止'][i % 3],
        file_path: `/files/contract_${i + 1}.pdf`
    }))
}

const tableData = ref<SupplierContract[]>(generateFakeContracts())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加合同')
const form = ref<Partial<SupplierContract>>({})
const formRef = ref<FormInstance | null>(null)
const fileList = ref<any[]>([])
const uploading = ref(false)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: SupplierContract) => {
    dialogTitle.value = row ? '编辑合同' : '添加合同'
    form.value = row ? { ...row } : {}
    fileList.value = []
    if (form.value.file_path) {
        fileList.value = [
            {
                name: form.value.file_path.split('/').pop() || '文件',
                url: form.value.file_path
            }
        ]
    }
    dialogVisible.value = true
}

const resetForm = () => {
    formRef.value?.clearValidate()
    form.value = {}
    fileList.value = []
    uploading.value = false
}

const handleSave = () => {
    if (form.value.contract_id) {
        const index = tableData.value.findIndex(item => item.contract_id === form.value.contract_id)
        if (index !== -1) {
            tableData.value[index] = form.value as SupplierContract
            ElMessage.success('合同更新成功')
        }
    } else {
        // 生成一个自增id
        const maxId = tableData.value.reduce((max, item) => (item.contract_id > max ? item.contract_id : max), 0)
        tableData.value.push({ ...(form.value as SupplierContract), contract_id: maxId + 1 })
        ElMessage.success('合同添加成功')
    }
    dialogVisible.value = false
}

const confirmDelete = (contract_id: number) => {
    ElMessageBox.confirm('确定删除此合同吗？', '提示', {
        type: 'warning'
    })
        .then(() => {
            handleDelete(contract_id)
            ElMessage.success('删除成功')
        })
        .catch(() => {
            // 取消删除
        })
}

const handleDelete = (contract_id: number) => {
    tableData.value = tableData.value.filter(item => item.contract_id !== contract_id)
    // 删除后如果当前页空了，回退一页
    if (paginatedData.value.length === 0 && currentPage.value > 1) {
        currentPage.value--
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const rules = {
    supplier_id: [{ required: true, message: '供应商ID不能为空', trigger: 'blur' }],
    start_date: [{ required: true, message: '请选择合同开始时间', trigger: 'change' }],
    end_date: [{ required: true, message: '请选择合同结束时间', trigger: 'change' }],
    contract_amount: [{ required: true, message: '合同金额不能为空', trigger: 'blur' }],
    status: [{ required: true, message: '请选择合同状态', trigger: 'change' }]
}

const handleUploadSuccess = (response: any, file: any) => {
    // 上传接口返回的真实路径，jsonplaceholder演示接口没有返回路径，这里演示用file.url
    const url = file.url || (response && response.url) || ''
    if (url) {
        form.value.file_path = url
        fileList.value = [{ name: file.name, url }]
        ElMessage.success('上传成功')
    } else {
        ElMessage.error('上传失败，无法获取文件路径')
    }
    uploading.value = false
}

const handleRemove = () => {
    form.value.file_path = ''
    fileList.value = []
}

const beforeUpload = (file: File) => {
    const isAllowed = [
        'application/pdf',
        'application/msword',
        'application/vnd.openxmlformats-officedocument.wordprocessingml.document'
    ].includes(file.type)
    const isLt5M = file.size / 1024 / 1024 < 5
    if (!isAllowed) {
        ElMessage.error('只支持pdf/doc/docx格式的文件')
    }
    if (!isLt5M) {
        ElMessage.error('文件大小不能超过5MB')
    }
    if (isAllowed && isLt5M) {
        uploading.value = true
    }
    return isAllowed && isLt5M
}

const submitForm = () => {
    formRef.value?.validate(valid => {
        if (valid) {
            handleSave()
        }
    })
}
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}

.upload-demo {
    width: 100%;
}
</style>
