<template>
    <el-container>
        <el-header>
            <el-button type="primary" @click="showCreateDialog">添加分类</el-button>
        </el-header>
        <el-main>
            <el-table :data="categories" border>
                <el-table-column prop="goods_category_id" label="分类ID" />
                <el-table-column prop="goods_category_name" label="分类名称" />
                <el-table-column prop="goods_category_description" label="分类描述" />
                <el-table-column prop="parent_category_id" label="父级分类ID" />
                <el-table-column label="操作">
                    <template #default="scope">
                        <el-button @click="showUpdateDialog(scope.row)" size="small">更新</el-button>
                        <el-button @click="deleteCategory(scope.row.goods_category_id)" size="small"
                            type="danger">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <el-pagination @current-change="handlePageChange" :current-page="page" :page-size="pageSize"
                :total="totalCategories" layout="total, prev, pager, next, jumper" />
        </el-main>

        <!-- 创建分类对话框 -->
        <el-dialog v-model="createDialogVisible" title="添加分类">
            <el-form :model="createForm" ref="createFormRef" label-width="120px">
                <el-form-item label="分类名称" prop="goods_category_name"
                    :rules="[{ required: true, message: '请输入分类名称', trigger: 'blur' }]">
                    <el-input v-model="createForm.goods_category_name" />
                </el-form-item>
                <el-form-item label="分类描述" prop="goods_category_description"
                    :rules="[{ required: true, message: '请输入分类描述', trigger: 'blur' }]">
                    <el-input v-model="createForm.goods_category_description" />
                </el-form-item>
                <el-form-item label="父级分类ID" prop="parent_category_id"
                    :rules="[{ required: true, message: '请输入父级分类ID', trigger: 'blur' }]">
                    <el-input-number v-model="createForm.parent_category_id" :min="0" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="createDialogVisible = false">取 消</el-button>
                <el-button type="primary" @click="createCategory">确 定</el-button>
            </template>
        </el-dialog>

        <!-- 更新分类对话框 -->
        <el-dialog v-model="updateDialogVisible" title="更新分类">
            <el-form :model="updateForm" ref="updateFormRef" label-width="120px">
                <el-form-item label="分类名称" prop="goods_category_name"
                    :rules="[{ required: true, message: '请输入分类名称', trigger: 'blur' }]">
                    <el-input v-model="updateForm.goods_category_name" />
                </el-form-item>
                <el-form-item label="分类描述" prop="goods_category_description"
                    :rules="[{ required: true, message: '请输入分类描述', trigger: 'blur' }]">
                    <el-input v-model="updateForm.goods_category_description" />
                </el-form-item>
                <el-form-item label="父级分类ID" prop="parent_category_id"
                    :rules="[{ required: true, message: '请输入父级分类ID', trigger: 'blur' }]">
                    <el-input-number v-model="updateForm.parent_category_id" :min="0" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="updateDialogVisible = false">取 消</el-button>
                <el-button type="primary" @click="updateCategory">确 定</el-button>
            </template>
        </el-dialog>
    </el-container>
</template>

<script setup lang="ts">
import { ref, reactive, toRaw, onMounted } from 'vue';
import axios from 'axios';

const categories = ref<any[]>([]);
const page = ref(1);
const pageSize = 10; // 固定10条/页
const totalCategories = ref(0);

const createDialogVisible = ref(false);
const updateDialogVisible = ref(false);

const createForm = reactive({
    goods_category_id: '',
    goods_category_name: '',
    goods_category_description: '',
    parent_category_id: 0,
});

const updateForm = reactive({
    goods_category_id: '',
    goods_category_name: '',
    goods_category_description: '',
    parent_category_id: 0,
});

const createFormRef = ref();
const updateFormRef = ref();

const fetchCategories = async () => {
    try {
        console.log('请求分页数据：', { page: page.value, page_size: pageSize });
        const res = await axios.post('/api/goods_category/get_by_page', {
            page: page.value,
            page_size: pageSize,
        });
        console.log('完整接口返回:', res);
        console.log('res.data:', res.data);
        console.log('res.data.data:', res.data.data);

        if (res.data && res.data.data) {
            categories.value = res.data.data.items || [];
            totalCategories.value = res.data.data.total || 0;
            console.log('获取分类数据成功:', res.data.data);
        } else {
            console.warn('接口返回结构不符合预期，缺少 data 字段');
            categories.value = [];
            totalCategories.value = 0;
        }
    } catch (err) {
        console.error('获取分类列表失败:', err);
    }
};

const handlePageChange = (newPage: number) => {
    page.value = newPage;
    fetchCategories();
};

const showCreateDialog = () => {
    createForm.goods_category_name = '';
    createForm.goods_category_description = '';
    createForm.parent_category_id = 0;
    createDialogVisible.value = true;
};

const createCategory = async () => {
    if (!createFormRef.value) return;
    (createFormRef.value as any).validate(async (valid: boolean) => {
        if (valid) {
            try {
                const payload = { ...createForm };
                console.log('创建分类请求:', payload);
                await axios.post('/api/goods_category/create', payload);
                createDialogVisible.value = false;
                page.value = 1; // 新增后跳回第一页
                await fetchCategories();
            } catch (err) {
                console.error('创建分类失败:', err);
            }
        } else {
            console.log('表单验证未通过，无法提交');
            return false;
        }
    });
};

const showUpdateDialog = (row: any) => {
    Object.assign(updateForm, row);
    updateDialogVisible.value = true;
};

const updateCategory = async () => {
    if (!updateFormRef.value) return;
    (updateFormRef.value as any).validate(async (valid: boolean) => {
        if (valid) {
            try {
                console.log('更新分类请求:', updateForm);
                await axios.post('/api/goods_category/update', { ...toRaw(updateForm) });
                updateDialogVisible.value = false;
                await fetchCategories();
            } catch (err) {
                console.error('更新分类失败:', err);
            }
        } else {
            console.log('表单验证未通过，无法提交');
            return false;
        }
    });
};

const deleteCategory = async (goods_category_id: any) => {
    const rawId = typeof goods_category_id === 'object' ? toRaw(goods_category_id) : goods_category_id;
    console.log('传入的删除ID类型:', typeof rawId, rawId);

    try {
        await axios.post(
            '/api/goods_category/remove',
            { goods_category_id: rawId },
            {
                headers: { 'Content-Type': 'application/json' },
            }
        );
        await fetchCategories();
        if (categories.value.length === 0 && page.value > 1) {
            page.value--;
            await fetchCategories();
        }
    } catch (err) {
        console.error('删除分类失败:', err);
    }
};

onMounted(() => {
    fetchCategories();
});
</script>

<style scoped>
/* 可自定义样式 */
</style>
