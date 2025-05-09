<template>
    <div class="goods-category-manager page-container">
        <el-card class="card" :body-style="{ padding: '20px' }">
            <h1>商品分类管理</h1>

            <!-- 商品分类创建/更新 -->
            <div class="create-form">
                <h2>{{ isEditing ? '编辑商品分类' : '创建商品分类' }}</h2>
                <el-input v-model="categoryName" placeholder="分类名称" class="form-input" />
                <el-input v-model="categoryDescription" placeholder="分类描述" class="form-input" />
                <el-select v-model="parentCategoryId" placeholder="选择上级分类" class="form-input">
                    <el-option :label="'无（顶级）'" :value="'0'" />
                    <el-option v-for="item in allCategories" :key="item.goods_category_id" :label="item.category_name"
                        :value="item.goods_category_id.toString()" />
                </el-select>
                <el-button :loading="loading" type="primary" @click="isEditing ? updateCategory() : createCategory()">
                    {{ isEditing ? '更新分类' : '创建分类' }}
                </el-button>
                <el-button v-if="isEditing" @click="cancelEdit">取消编辑</el-button>
            </div>

            <!-- 商品分类列表 -->
            <div class="category-list">
                <h2>商品分类列表</h2>
                <el-table :data="categories.items" style="width: 100%">
                    <el-table-column label="分类ID" prop="goods_category_id" />
                    <el-table-column label="分类名称" prop="category_name" />
                    <el-table-column label="分类描述" prop="category_description" />
                    <el-table-column label="上级分类ID" prop="parent_category_id" />
                    <el-table-column label="操作" width="150">
                        <template v-slot="scope">
                            <el-button @click="editCategory(scope.row)" type="text" size="small">修改</el-button>
                            <el-button @click="deleteCategory(scope.row.goods_category_id)" type="text" size="small"
                                class="red-button">删除</el-button>
                        </template>
                    </el-table-column>
                </el-table>

                <!-- 分页 -->
                <div class="pagination" v-if="categories.total > categories.page_size">
                    <el-pagination background layout="prev, pager, next" :page-size="categories.page_size"
                        :total="categories.total" :current-page="categories.page" @current-change="handlePageChange" />
                </div>
            </div>
        </el-card>
    </div>
</template>

<script>
import axios from 'axios';
import { ElMessage, ElTable, ElTableColumn, ElButton, ElCard, ElInput, ElPagination, ElSelect, ElOption } from 'element-plus';

export default {
    data() {
        return {
            categoryName: '',
            categoryDescription: '',
            parentCategoryId: '0',
            editingCategoryId: null,
            isEditing: false,
            loading: false,
            categories: {
                items: [],
                page: 1,
                page_size: 10,
                total: 0
            },
            allCategories: [] // 用于上级分类下拉选择
        };
    },
    methods: {
        async createCategory() {
            if (!this.categoryName || !this.categoryDescription) {
                ElMessage.warning('分类名称和描述不能为空');
                return;
            }
            this.loading = true;
            try {
                const response = await axios.post('http://localhost:8080/api/goods_category/create', {
                    category_name: this.categoryName,
                    category_description: this.categoryDescription,
                    parent_category_id: this.parentCategoryId
                });
                if (response.data.code === 201) {
                    ElMessage.success('商品分类创建成功');
                    this.clearForm();
                    this.loadCategories();
                    this.loadAllCategories();
                } else {
                    ElMessage.error('创建失败');
                }
            } catch (error) {
                console.error('创建请求失败', error);
                ElMessage.error('请求失败');
            } finally {
                this.loading = false;
            }
        },

        async updateCategory() {
            if (!this.categoryName || !this.categoryDescription) {
                ElMessage.warning('分类名称和描述不能为空');
                return;
            }
            this.loading = true;
            try {
                const response = await axios.post('http://localhost:8080/api/goods_category/update', {
                    goods_category_id: this.editingCategoryId,
                    category_name: this.categoryName,
                    category_description: this.categoryDescription,
                    parent_category_id: this.parentCategoryId
                });
                if (response.data.code === 200) {
                    ElMessage.success('商品分类更新成功');
                    this.clearForm();
                    this.loadCategories();
                    this.loadAllCategories();
                    this.isEditing = false;
                    this.editingCategoryId = null;
                } else {
                    ElMessage.error('更新失败');
                }
            } catch (error) {
                console.error('更新请求失败', error);
                ElMessage.error('请求失败');
            } finally {
                this.loading = false;
            }
        },

        async deleteCategory(goodsCategoryId) {
            try {
                const response = await axios.post('http://localhost:8080/api/goods_category/remove', {
                    goods_category_id: goodsCategoryId
                });
                if (response.data.code === 200) {
                    ElMessage.success('商品分类删除成功');
                    this.loadCategories();
                    this.loadAllCategories();
                } else {
                    ElMessage.error('删除失败');
                }
            } catch (error) {
                console.error('删除请求失败', error);
                ElMessage.error('请求失败');
            }
        },

        editCategory(category) {
            this.categoryName = category.category_name;
            this.categoryDescription = category.category_description;
            this.parentCategoryId = category.parent_category_id.toString();
            this.editingCategoryId = category.goods_category_id;
            this.isEditing = true;
        },

        cancelEdit() {
            this.clearForm();
            this.isEditing = false;
            this.editingCategoryId = null;
        },

        async loadCategories() {
            try {
                const response = await axios.post('http://localhost:8080/api/goods_category/get_by_page', {
                    page: this.categories.page,
                    page_size: this.categories.page_size
                });
                if (response.data.code === 200) {
                    this.categories = response.data.data;
                } else {
                    ElMessage.error('加载失败');
                }
            } catch (error) {
                console.error('加载请求失败', error);
                ElMessage.error('请求失败');
            }
        },

        async loadAllCategories() {
            try {
                const response = await axios.post('http://localhost:8080/api/goods_category/get_all');
                if (response.data.code === 200) {
                    this.allCategories = response.data.data;
                }
            } catch (error) {
                console.error('加载所有分类失败', error);
            }
        },

        handlePageChange(newPage) {
            this.categories.page = newPage;
            this.loadCategories();
        },

        clearForm() {
            this.categoryName = '';
            this.categoryDescription = '';
            this.parentCategoryId = '0';
        }
    },
    mounted() {
        this.loadCategories();
        this.loadAllCategories();
    },
    components: {
        ElTable,
        ElTableColumn,
        ElButton,
        ElCard,
        ElInput,
        ElPagination,
        ElSelect,
        ElOption
    }
};
</script>

<style scoped>
.goods-category-manager {
    padding: 20px;
}

.card {
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    border-radius: 10px;
}

.create-form {
    margin-bottom: 20px;
}

.form-input {
    margin-bottom: 10px;
    width: 100%;
}

.category-list {
    margin-top: 20px;
}

.pagination {
    margin-top: 16px;
    text-align: right;
}

.el-table .el-button {
    margin-right: 10px;
}

.el-table .el-button--text {
    color: #409EFF;
}

.el-table .el-button--text.red-button {
    color: red;
}
</style>
