<template>
    <el-container>
        <el-header>
            <el-button type="primary" @click="showCreateDialog">添加分类</el-button>
        </el-header>
        <el-main>
            <el-table :data="categories" border style="width: 100%">
                <el-table-column prop="goods_category_id" label="分类ID" />
                <el-table-column prop="goods_category_name" label="分类名称" />
                <el-table-column prop="goods_category_description" label="分类描述" />
                <el-table-column prop="parent_category_id" label="父级分类ID" />
                <el-table-column label="操作" width="180">
                    <template #default="scope">
                        <el-button size="small" @click="showUpdateDialog(scope.row)">更新</el-button>
                        <el-button size="small" type="danger"
                            @click="deleteCategory(scope.row.goods_category_id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>
        </el-main>

        <!-- 添加弹窗 -->
        <el-dialog v-model="createDialogVisible" title="添加分类" width="500px">
            <el-form ref="createFormRef" :model="createForm" :rules="formRules" label-width="120px">
                <el-form-item label="分类名称" prop="goods_category_name">
                    <el-input v-model="createForm.goods_category_name" />
                </el-form-item>
                <el-form-item label="分类描述" prop="goods_category_description">
                    <el-input v-model="createForm.goods_category_description" />
                </el-form-item>
                <el-form-item label="父级分类ID" prop="parent_category_id">
                    <el-input-number v-model="createForm.parent_category_id" :min="0" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="createDialogVisible = false">取消</el-button>
                <el-button type="primary" @click="createCategory">确认</el-button>
            </template>
        </el-dialog>

        <!-- 更新弹窗 -->
        <el-dialog v-model="updateDialogVisible" title="更新分类" width="500px">
            <el-form ref="updateFormRef" :model="updateForm" :rules="formRules" label-width="120px">
                <el-form-item label="分类名称" prop="goods_category_name">
                    <el-input v-model="updateForm.goods_category_name" />
                </el-form-item>
                <el-form-item label="分类描述" prop="goods_category_description">
                    <el-input v-model="updateForm.goods_category_description" />
                </el-form-item>
                <el-form-item label="父级分类ID" prop="parent_category_id">
                    <el-input-number v-model="updateForm.parent_category_id" :min="0" />
                </el-form-item>
            </el-form>
            <template #footer>
                <el-button @click="updateDialogVisible = false">取消</el-button>
                <el-button type="primary" @click="updateCategory">确认</el-button>
            </template>
        </el-dialog>
    </el-container>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted, toRaw } from 'vue';
import { ElMessage } from 'element-plus';
import axios from 'axios';

const API_BASE = '/api/goods_category'; // 统一接口基础路径

interface Category {
    goods_category_id: number | string;
    goods_category_name: string;
    goods_category_description: string;
    parent_category_id: number;
}

const categories = ref<Category[]>([]);

const createDialogVisible = ref(false);
const updateDialogVisible = ref(false);

const createForm = reactive<Omit<Category, 'goods_category_id'>>({
    goods_category_name: '',
    goods_category_description: '',
    parent_category_id: 0,
});

const updateForm = reactive<Category>({
    goods_category_id: '',
    goods_category_name: '',
    goods_category_description: '',
    parent_category_id: 0,
});

const createFormRef = ref();
const updateFormRef = ref();

const formRules = {
    goods_category_name: [{ required: true, message: '请输入分类名称', trigger: 'blur' }],
};

const fetchCategories = async () => {
    try {
        const res = await axios.get(API_BASE + '/get_all');
        if (res.data?.code === 200 && res.data.data?.items) {
            categories.value = res.data.data.items;  // 取到真正的数组
            ElMessage.success('获取分类成功');
        } else {
            categories.value = [];
            ElMessage.error('返回数据格式不正确');
        }
    } catch (error) {
        ElMessage.error('获取分类失败');
        console.error(error);
    }
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
                await axios.post(`${API_BASE}/create`, payload);
                createDialogVisible.value = false;
                ElMessage.success('添加分类成功');
                await fetchCategories();
            } catch (err) {
                console.error('创建分类失败:', err);
                ElMessage.error('创建分类失败');
            }
        }
    });
};

const showUpdateDialog = (row: Category) => {
    Object.assign(updateForm, row);
    updateDialogVisible.value = true;
};

const updateCategory = async () => {
    if (!updateFormRef.value) return;
    (updateFormRef.value as any).validate(async (valid: boolean) => {
        if (valid) {
            try {
                const payload = toRaw(updateForm);
                await axios.post(`${API_BASE}/update`, payload);
                updateDialogVisible.value = false;
                ElMessage.success('更新分类成功');
                await fetchCategories();
            } catch (err) {
                console.error('更新分类失败:', err);
                ElMessage.error('更新分类失败');
            }
        }
    });
};

const deleteCategory = async (id: number | string) => {
    try {
        await axios.post(`${API_BASE}/remove`, { goods_category_id: id });
        ElMessage.success('删除分类成功');
        await fetchCategories();
    } catch (err) {
        console.error('删除分类失败:', err);
        ElMessage.error('删除分类失败');
    }
};

onMounted(() => {
    fetchCategories();
});
</script>
