<template>
    <el-card>
        <h2>商品库存管理</h2>
        <div class="toolbar">
            <el-button type="primary" @click="openDialog()">添加商品</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column prop="id" label="商品ID" width="100" />
            <el-table-column prop="name" label="商品名称" />
            <el-table-column prop="stock" label="库存数量" />
            <el-table-column prop="warehouse_name" label="仓库名称" width="150" />
            <el-table-column label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">更新</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row.id)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange"
            layout="prev, pager, next, jumper"></el-pagination>

        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="400px">
            <el-form :model="form" ref="formRef">
                <el-form-item label="商品名称" :label-width="formLabelWidth" required>
                    <el-input v-model="form.name" autocomplete="off" />
                </el-form-item>
                <el-form-item label="库存数量" :label-width="formLabelWidth" required>
                    <el-input-number v-model="form.stock" :min="0" style="width: 100%;" />
                </el-form-item>
                <el-form-item label="仓库名称" :label-width="formLabelWidth" required>
                    <el-select v-model="form.warehouse_name" filterable allow-create placeholder="请选择或输入仓库名称"
                        style="width: 100%;" :default-first-option="true" :filter-method="filterWarehouseNames"
                        @clear="searchKeyword = ''">
                        <el-option v-for="item in filteredWarehouseNames" :key="item" :label="item" :value="item" />
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
import { ElMessage } from 'element-plus'

interface Product {
    id: number
    name: string
    stock: number
    warehouse_name?: string
}

const warehouseNames = ['东区仓库', '西区仓库', '南区仓库', '北区仓库', '中区仓库']

const generateFakeProducts = (count: number): Product[] => {
    const productNames = ['可乐', '牛奶', '面包', '饼干', '泡面', '鸡蛋', '矿泉水', '牙膏', '洗发水', '纸巾']
    return Array.from({ length: count }, (_, index) => ({
        id: index + 1,
        name: productNames[Math.floor(Math.random() * productNames.length)] + (index + 1),
        stock: Math.floor(Math.random() * 500) + 1,
        warehouse_name: warehouseNames[Math.floor(Math.random() * warehouseNames.length)],
    }))
}

const tableData = ref<Product[]>(generateFakeProducts(53))
const dialogVisible = ref(false)
const dialogTitle = ref('添加商品')
const form = ref<Partial<Product>>({ warehouse_name: '' })

const currentPage = ref(1)
const pageSize = ref(10)
const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

// 绑定在 el-select filter-method 中的关键字，用于筛选仓库名称
const searchKeyword = ref('')

const filteredWarehouseNames = computed(() => {
    if (!searchKeyword.value) return warehouseNames
    return warehouseNames.filter(name => name.includes(searchKeyword.value))
})

// el-select 的自定义过滤方法，赋值 searchKeyword，保持过滤同步
const filterWarehouseNames = (query: string) => {
    searchKeyword.value = query
}

const openDialog = (row?: Product) => {
    dialogTitle.value = row ? '编辑商品' : '添加商品'
    form.value = row ? { ...row } : { warehouse_name: '' }
    searchKeyword.value = ''
    dialogVisible.value = true
}

const handleSave = () => {
    if (!form.value.name?.trim()) {
        ElMessage.warning('商品名称不能为空')
        return
    }
    if (!form.value.warehouse_name?.trim()) {
        ElMessage.warning('仓库名称不能为空')
        return
    }

    if (form.value.id) {
        const index = tableData.value.findIndex(item => item.id === form.value.id)
        if (index !== -1) {
            tableData.value[index] = { ...(form.value as Product) }
        }
    } else {
        const newId = tableData.value.length ? Math.max(...tableData.value.map(item => item.id)) + 1 : 1
        tableData.value.push({
            id: newId,
            name: form.value.name!,
            stock: form.value.stock || 0,
            warehouse_name: form.value.warehouse_name!,
        })
    }

    ElMessage.success('保存成功')
    dialogVisible.value = false
}

const handleDelete = (id: number) => {
    tableData.value = tableData.value.filter(item => item.id !== id)
    ElMessage.success('删除成功')
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const formLabelWidth = '100px'
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style>
