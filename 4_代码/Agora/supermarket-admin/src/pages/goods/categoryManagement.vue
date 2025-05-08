<template>
    <div>
        <!-- 商品分类创建表单 -->
        <el-form :model="categoryForm" ref="categoryForm" label-width="120px">
            <el-form-item label="Category Name" prop="category_name">
                <el-input v-model="categoryForm.category_name" placeholder="Enter category name" />
            </el-form-item>
            <el-form-item label="Category Description" prop="category_description">
                <el-input v-model="categoryForm.category_description" placeholder="Enter category description" />
            </el-form-item>
            <el-form-item label="Parent Category ID" prop="parent_category_id">
                <el-input v-model="categoryForm.parent_category_id" placeholder="Enter parent category ID" />
            </el-form-item>
            <el-button type="primary" @click="submitForm">Create Category</el-button>
        </el-form>

        <!-- 商品分类列表 -->
        <el-table :data="categoryList" style="width: 100%">
            <el-table-column label="Category Name" prop="category_name"></el-table-column>
            <el-table-column label="Description" prop="category_description"></el-table-column>
            <el-table-column label="Parent Category ID" prop="parent_category_id"></el-table-column>
            <el-table-column label="Actions">
                <template #default="{ row }">
                    <el-button @click="editCategory(row)">Edit</el-button>
                    <el-button type="danger" @click="deleteCategory(row.goods_category_id)">Delete</el-button>
                </template>
            </el-table-column>
        </el-table>

        <!-- 分页 -->
        <el-pagination :current-page="page" :page-size="pageSize" :total="totalItems" @current-change="fetchCategories"
            layout="total, prev, pager, next, jumper" />
    </div>
</template>

<script>
import { createGoodsCategory, getGoodsCategoriesByPage, deleteGoodsCategory, updateGoodsCategory } from '../../api/goods_api/goodsCategory.ts'

export default {
    data() {
        return {
            categoryForm: {
                category_name: '',
                category_description: '',
                parent_category_id: ''
            },
            categoryList: [],
            page: 1,
            pageSize: 10,
            totalItems: 0
        }
    },
    methods: {
        // 提交表单，创建商品分类
        async submitForm() {
            try {
                const response = await createGoodsCategory(this.categoryForm)
                if (response.success) {
                    this.$message.success('Category created successfully')
                    this.fetchCategories()
                }
            } catch (error) {
                this.$message.error('Error creating category')
            }
        },

        // 获取商品分类列表
        async fetchCategories(page = this.page) {
            try {
                const response = await getGoodsCategoriesByPage({ page, page_size: this.pageSize })
                this.categoryList = response.data
                this.totalItems = response.total
            } catch (error) {
                this.$message.error('Error fetching categories')
            }
        },

        // 编辑商品分类
        editCategory(row) {
            this.categoryForm = { ...row } // 预填表单数据
        },

        // 删除商品分类
        async deleteCategory(categoryId) {
            try {
                const response = await deleteGoodsCategory({ goods_category_id: categoryId })
                if (response.success) {
                    this.$message.success('Category deleted successfully')
                    this.fetchCategories()
                }
            } catch (error) {
                this.$message.error('Error deleting category')
            }
        },

        // 分页改变时重新获取数据
        handlePageChange(page) {
            this.page = page
            this.fetchCategories(page)
        }
    },
    mounted() {
        this.fetchCategories()  // 页面加载时获取分类列表
    }
}
</script>

<style scoped>
.el-table {
    margin-top: 20px;
}
</style>