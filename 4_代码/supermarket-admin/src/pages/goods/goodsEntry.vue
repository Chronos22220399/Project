<template>
    <div>
        <!-- 弹窗：创建/编辑商品 -->
        <el-dialog v-model="dialogVisible" :title="isEdit ? '编辑商品' : '创建商品'" width="50%">
            <el-form :model="product" :rules="rules" ref="productForm" label-width="100px">
                <el-form-item label="商品名称" prop="goods_name">
                    <el-autocomplete v-model="product.goods_name" :fetch-suggestions="querySearch" placeholder="请输入商品名称"
                        clearable />
                </el-form-item>

                <el-form-item label="分类" prop="category_id">
                    <el-select v-model="product.category_id" placeholder="请选择分类">
                        <el-option v-for="item in categories" :key="item.id" :label="item.name" :value="item.id" />
                    </el-select>
                </el-form-item>

                <el-form-item label="供应商" prop="supplier_id">
                    <el-select v-model="product.supplier_id" placeholder="请选择供应商">
                        <el-option v-for="item in suppliers" :key="item.id" :label="item.name" :value="item.id" />
                    </el-select>
                </el-form-item>

                <el-form-item label="单位" prop="unit_id">
                    <el-select v-model="product.unit_id" placeholder="请选择单位">
                        <el-option v-for="item in units" :key="item.id" :label="item.name" :value="item.id" />
                    </el-select>
                </el-form-item>

                <el-form-item label="保质期天数" prop="shelf_life_days">
                    <el-input-number v-model="product.shelf_life_days" :min="0" />
                </el-form-item>

                <el-form-item label="条形码" prop="barcode">
                    <el-input v-model="product.barcode" placeholder="可由图片自动识别" />
                </el-form-item>

                <el-form-item label="商品图片" prop="image_url">
                    <el-upload class="avatar-uploader" action="" :auto-upload="false" :show-file-list="false"
                        :on-change="handleImageChange">
                        <img v-if="product.image_url" :src="product.image_url" class="preview" />
                        <el-icon v-else>
                            <Plus />
                        </el-icon>
                    </el-upload>
                </el-form-item>

                <el-form-item label="描述" prop="description">
                    <el-input type="textarea" v-model="product.description" rows="3" />
                </el-form-item>

                <el-form-item>
                    <el-button type="primary" @click="submitProduct">{{ isEdit ? '保存修改' : '提交' }}</el-button>
                    <el-button @click="dialogVisible = false">取消</el-button>
                </el-form-item>
            </el-form>
        </el-dialog>

        <!-- 商品详情 -->
        <el-card class="mt-4">
            <el-button type="primary" @click="openCreateDialog">创建商品</el-button>
            <h2>商品详情</h2>
            <el-form :model="productDetail" label-width="100px">
                <el-form-item label="商品ID">
                    <el-select v-model="goods_id" placeholder="请选择商品">
                        <el-option v-for="item in goodsList" :key="item.goods_id" :label="item.goods_name"
                            :value="item.goods_id" />
                    </el-select>
                </el-form-item>
                <el-button type="primary" @click="getProductDetails">获取详情</el-button>
                <div v-if="productDetail">
                    <el-form-item label="商品名称"><span>{{ productDetail.goods_name }}</span></el-form-item>
                    <el-form-item label="库存"><span>{{ productDetail.stock }}</span></el-form-item>
                    <el-form-item label="单位"><span>{{ productDetail.unit }}</span></el-form-item>
                    <el-form-item label="仓库名称"><span>{{ productDetail.warehouse_name }}</span></el-form-item>
                    <el-form-item label="位置"><span>{{ productDetail.location }}</span></el-form-item>
                    <el-form-item label="保质期"><span>{{ productDetail.shelf_life_days }} 天</span></el-form-item>
                </div>
            </el-form>
        </el-card>

        <!-- 商品列表 -->
        <el-card class="mt-4">
            <h2>商品列表</h2>
            <el-table :data="pagedGoods" style="width: 100%" border>
                <el-table-column label="商品ID" prop="goods_id" />
                <el-table-column label="商品名称" prop="goods_name" />
                <el-table-column label="分类" prop="category_name" />
                <el-table-column label="库存" prop="stock" />
                <el-table-column label="供应商" prop="supplier_name" />
                <el-table-column label="单位" prop="unit_name" />
                <el-table-column label="操作">
                    <template #default="scope">
                        <el-button size="small" @click="openEditDialog(scope.row)">更新</el-button>
                        <el-button size="small" type="danger" @click="deleteProduct(scope.row.goods_id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <el-pagination class="mt-2" layout="total, prev, pager, next" :total="goodsList.length"
                :page-size="pageSize" :current-page="currentPage" @current-change="handlePageChange" />
        </el-card>
    </div>
</template>

<script lang="ts">
import { defineComponent, ref, computed } from 'vue';
import { ElMessage, ElForm, ElMessageBox } from 'element-plus';
import { Plus } from '@element-plus/icons-vue';

export default defineComponent({
    name: 'GoodsManager',
    components: { Plus },
    setup() {
        const dialogVisible = ref(false);
        const isEdit = ref(false);
        const editId = ref<number | null>(null);

        const categories = [
            { id: 'CAT001', name: '饮料' },
            { id: 'CAT002', name: '零食' },
            { id: 'CAT003', name: '生鲜' },
        ];
        const suppliers = [
            { id: 'SUP001', name: '供应商A' },
            { id: 'SUP002', name: '供应商B' },
            { id: 'SUP003', name: '供应商C' },
        ];
        const units = [
            { id: 'UNIT001', name: '件' },
            { id: 'UNIT002', name: '瓶' },
            { id: 'UNIT003', name: '箱' },
        ];

        const product = ref({
            goods_name: '',
            category_id: '',
            supplier_id: '',
            unit_id: '',
            shelf_life_days: 0,
            barcode: '',
            image_url: '',
            description: '',
        });

        const productForm = ref<InstanceType<typeof ElForm>>();
        const rules = {
            goods_name: [{ required: true, message: '请输入商品名称', trigger: 'blur' },
            {
                pattern: /^[\u4e00-\u9fa5a-zA-Z0-9 ]+$/,
                message: '商品名称不能包含特殊字符',
                trigger: 'blur'
            }
            ],
            category_id: [{ required: true, message: '请选择分类', trigger: 'change' }],
            supplier_id: [{ required: true, message: '请选择供应商', trigger: 'change' }],
            unit_id: [{ required: true, message: '请选择单位', trigger: 'change' }],
            shelf_life_days: [{ required: true, message: '请输入保质期', trigger: 'blur' }],
            barcode: [{ required: true, message: '请输入条形码', trigger: 'blur' },
            {
                pattern: /^[a-zA-Z0-9]+$/,
                message: '条形码只能包含字母和数字',
                trigger: 'blur'
            }
            ],
            image_url: [{ required: true, message: '请上传图片', trigger: 'change' }],
            description: [{ required: true, message: '请输入描述', trigger: 'blur' }],
        };

        const goodsList = ref<any[]>(Array.from({ length: 25 }, (_, i) => ({
            goods_id: i + 1,
            goods_name: `商品${i + 1}`,
            category_id: 'CAT00' + ((i % 3) + 1),
            category_name: categories[i % 3].name,
            stock: Math.floor(Math.random() * 100),
            supplier_id: suppliers[i % 3].id,
            supplier_name: suppliers[i % 3].name,
            unit_id: units[i % 3].id,
            unit_name: units[i % 3].name,
        })));

        const goodsNameSuggestions = ref(goodsList.value.map(item => ({
            value: item.goods_name
        })));

        const querySearch = (queryString: string, cb: Function) => {
            const results = goodsNameSuggestions.value.filter(item =>
                item.value.toLowerCase().includes(queryString.toLowerCase())
            );
            cb(results);
        };


        const currentPage = ref(1);
        const pageSize = 10;
        const pagedGoods = computed(() => {
            const start = (currentPage.value - 1) * pageSize;
            return goodsList.value.slice(start, start + pageSize);
        });

        const handlePageChange = (val: number) => {
            currentPage.value = val;
        };

        const productDetail = ref<any>(null);
        const goods_id = ref();

        const getProductDetails = () => {
            const item = goodsList.value.find(g => g.goods_id === goods_id.value);
            if (item) {
                productDetail.value = {
                    ...item,
                    unit: item.unit_name,
                    warehouse_name: '测试仓库',
                    location: 'A区B层',
                    shelf_life_days: 365,
                };
            } else {
                ElMessage.error('未找到商品');
            }
        };

        const openCreateDialog = () => {
            isEdit.value = false;
            editId.value = null;
            dialogVisible.value = true;
            productForm.value?.resetFields();
        };

        const openEditDialog = (row: any) => {
            isEdit.value = true;
            editId.value = row.goods_id;
            dialogVisible.value = true;
            Object.assign(product.value, {
                goods_name: row.goods_name,
                category_id: row.category_id,
                supplier_id: row.supplier_id,
                unit_id: row.unit_id,
                shelf_life_days: 365,
                barcode: '模拟条形码',
                image_url: '',
                description: '示例描述',
            });
        };

        const submitProduct = () => {
            productForm.value?.validate((valid) => {
                if (!valid) ElMessage.warning('请填写完整信息');

                const category = categories.find(c => c.id === product.value.category_id)?.name || '';
                const supplier = suppliers.find(s => s.id === product.value.supplier_id)?.name || '';
                const unit = units.find(u => u.id === product.value.unit_id)?.name || '';

                if (isEdit.value && editId.value !== null) {
                    const index = goodsList.value.findIndex(g => g.goods_id === editId.value);
                    if (index !== -1) {
                        goodsList.value[index] = {
                            ...goodsList.value[index],
                            goods_name: product.value.goods_name,
                            category_id: product.value.category_id,
                            category_name: category,
                            supplier_id: product.value.supplier_id,
                            supplier_name: supplier,
                            unit_id: product.value.unit_id,
                            unit_name: unit,
                        };
                        ElMessage.success('商品更新成功');
                    }
                } else {
                    const newId = goodsList.value.length + 1;
                    goodsList.value.unshift({
                        goods_id: newId,
                        goods_name: product.value.goods_name,
                        category_id: product.value.category_id,
                        category_name: category,
                        stock: Math.floor(Math.random() * 100),
                        supplier_id: product.value.supplier_id,
                        supplier_name: supplier,
                        unit_id: product.value.unit_id,
                        unit_name: unit,
                    });
                    ElMessage.success('商品创建成功');
                }
                dialogVisible.value = false;
            });
        };

        const deleteProduct = (id: number) => {
            try {
                ElMessageBox.confirm(
                    '确定要删除这个商品吗？此操作不可撤销！',
                    '确认删除',
                    {
                        confirmButtonText: '确定',
                        cancelButtonText: '取消',
                        type: 'warning',
                    }
                );
                // 模拟删除
                goodsList.value = goodsList.value.filter(item => item.goods_id !== id);
                ElMessage.success('删除成功');
            } catch {
                ElMessage.info('已取消删除');
            }
        };

        const handleImageChange = (file: any) => {
            const reader = new FileReader();
            reader.onload = () => {
                product.value.image_url = reader.result as string;
                // 模拟条形码识别
                product.value.barcode = 'DEMO123456789';
                ElMessage.info('已识别条形码:DEMO123456789');
            };
            reader.readAsDataURL(file.raw);
        };



        return {
            dialogVisible,
            isEdit,
            product,
            productForm,
            rules,
            categories,
            suppliers,
            units,
            goodsList,
            pagedGoods,
            currentPage,
            pageSize,
            handlePageChange,
            openCreateDialog,
            openEditDialog,
            submitProduct,
            deleteProduct,
            productDetail,
            goods_id,
            getProductDetails,
            handleImageChange,
            querySearch,
        };
    }
});
</script>

<style scoped>
.mt-4 {
    margin-top: 1.5rem;
}

.preview {
    width: 100px;
    height: 100px;
    object-fit: cover;
}
</style>
