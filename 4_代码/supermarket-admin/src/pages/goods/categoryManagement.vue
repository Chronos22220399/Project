<template>
    <div class="page-container">
        <el-card>
            <template #header>
                <div class="flex justify-between items-center">
                    <h2>商品分类管理</h2>
                </div>
                <el-button type="primary" @click="openDialog">新增分类</el-button>
            </template>

            <el-table :data="categoryList" style="width: 100%">
                <el-table-column prop="goods_category_id" label="分类ID" width="100" />
                <el-table-column prop="category_name" label="分类名称" />
                <el-table-column prop="category_description" label="分类描述" />
                <el-table-column prop="parent_category_id" label="上级分类ID" width="120" />
                <el-table-column label="操作" width="180">
                    <template #default="scope">
                        <el-button size="small" @click="editCategory(scope.row)">更新</el-button>
                        <el-button size="small" type="danger"
                            @click="deleteCategory(scope.row.goods_category_id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <!-- 分页 -->
            <div class="mt-4 text-right">
                <el-pagination background layout="prev, pager, next" :current-page="currentPage" :page-size="pageSize"
                    :total="total" @current-change="handlePageChange" />
            </div>
        </el-card>

        <!-- 弹窗表单 -->
        <el-dialog :title="isEdit ? '编辑分类' : '新增分类'" v-model="dialogVisible" width="500px">
            <el-form :model="form" label-width="100px">
                <el-form-item label="分类名称">
                    <el-input v-model="form.category_name" />
                </el-form-item>
                <el-form-item label="分类描述">
                    <el-input v-model="form.category_description" />
                </el-form-item>
                <el-form-item label="上级分类">
                    <el-select v-model="form.parent_category_id" placeholder="选择上级分类">
                        <el-option label="无（顶级）" value="0" />
                        <el-option v-for="item in categoryList" :key="item.goods_category_id"
                            :label="item.category_name" :value="item.goods_category_id.toString()" />
                    </el-select>
                </el-form-item>
            </el-form>

            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="submitForm">提交</el-button>
            </template>
        </el-dialog>
    </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'

interface GoodsCategory {
    goods_category_id: number
    category_name: string
    category_description: string
    parent_category_id: string
}

// 生成随机商品分类数据
const generateRandomData = (): GoodsCategory[] => {
    const categories = ['饮料', '零食', '方便食品', '生活用品', '乳制品']
    const randomData: GoodsCategory[] = []
    for (let i = 1; i <= 50; i++) {
        const parentCategoryIndex = Math.floor(Math.random() * categories.length)
        randomData.push({
            goods_category_id: i,
            category_name: `${categories}子类${i}`,
            category_description: `${categories[parentCategoryIndex]}的描述${i}`,
            parent_category_id: (parentCategoryIndex + 1).toString(),
        })
    }
    return randomData
}

const categoryList = ref<GoodsCategory[]>(generateRandomData())
const dialogVisible = ref(false)
const isEdit = ref(false)
const form = ref<GoodsCategory>({
    goods_category_id: 0,
    category_name: '',
    category_description: '',
    parent_category_id: '0'
})

const currentPage = ref(1)
const pageSize = ref(10)
const total = ref(categoryList.value.length)

const loadData = () => {
    const start = (currentPage.value - 1) * pageSize.value
    const end = start + pageSize.value
    categoryList.value = generateRandomData().slice(start, end)
    total.value = 50 // 随机数据总数
}

const handlePageChange = (page: number) => {
    currentPage.value = page
    loadData()
}

const openDialog = () => {
    isEdit.value = false
    form.value = {
        goods_category_id: Date.now(),
        category_name: '',
        category_description: '',
        parent_category_id: '0'
    }
    dialogVisible.value = true
}

const editCategory = (item: GoodsCategory) => {
    isEdit.value = true
    form.value = { ...item }
    dialogVisible.value = true
}

const deleteCategory = (id: number) => {
    ElMessageBox.confirm('确定要删除该分类吗？', '提示', {
        type: 'warning'
    }).then(() => {
        const index = categoryList.value.findIndex(item => item.goods_category_id === id)
        if (index !== -1) {
            categoryList.value.splice(index, 1)
            ElMessage.success('删除成功')
            loadData()
        }
    })
}

const submitForm = () => {
    const index = categoryList.value.findIndex(item => item.goods_category_id === form.value.goods_category_id)
    if (isEdit.value && index !== -1) {
        categoryList.value[index] = { ...form.value }
        ElMessage.success('更新成功')
    } else {
        categoryList.value.push({ ...form.value })
        ElMessage.success('添加成功')
    }
    dialogVisible.value = false
    loadData()
}

onMounted(() => {
    loadData()
})
</script>

<style scoped>
.page-container {
    padding: 16px;
}
</style>
