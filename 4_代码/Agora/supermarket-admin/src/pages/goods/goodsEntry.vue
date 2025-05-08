<template>
    <div class="page-container">
        <el-row :gutter="20">
            <!-- 左侧：商品信息录入 -->
            <el-col :span="10">
                <el-card shadow="hover">
                    <template #header>
                        <span>商品信息录入</span>
                    </template>
                    <el-form :model="productForm" label-width="100px">
                        <el-form-item label="商品名称">
                            <el-input v-model="productForm.goods_name" placeholder="请输入商品名称" />
                        </el-form-item>
                        <el-form-item label="商品描述">
                            <el-input v-model="productForm.goods_description" type="textarea" placeholder="请输入商品描述" />
                        </el-form-item>
                        <el-form-item label="价格">
                            <el-input v-model="productForm.goods_price" type="number" placeholder="请输入价格" />
                        </el-form-item>
                        <el-form-item label="库存数量">
                            <el-input v-model="productForm.goods_stock" type="number" placeholder="请输入库存数量" />
                        </el-form-item>
                        <el-form-item label="分类ID">
                            <el-select v-model="productForm.category_id" placeholder="请选择分类ID">
                                <el-option v-for="item in categoryOptions" :key="item.value" :label="item.label"
                                    :value="item.value" />
                            </el-select>
                        </el-form-item>
                        <el-form-item label="供应商ID">
                            <el-select v-model="productForm.supplier_id" placeholder="请选择供应商ID">
                                <el-option v-for="item in supplierOptions" :key="item.value" :label="item.label"
                                    :value="item.value" />
                            </el-select>
                        </el-form-item>
                        <el-form-item label="单位ID">
                            <el-select v-model="productForm.unit_id" placeholder="请选择单位ID">
                                <el-option v-for="item in unitOptions" :key="item.value" :label="item.label"
                                    :value="item.value" />
                            </el-select>
                        </el-form-item>

                        <el-form-item>
                            <el-button type="primary" @click="submitProduct">提交</el-button>
                        </el-form-item>
                    </el-form>
                </el-card>
            </el-col>

            <!-- 右侧：商品列表 -->
            <el-col :span="14">
                <el-card shadow="hover">
                    <template #header>
                        <span>商品列表</span>
                    </template>
                    <el-table :data="goodsList" style="width: 100%">
                        <el-table-column label="商品ID" prop="goods_id" />
                        <el-table-column label="名称" prop="goods_name" />
                        <el-table-column label="价格" prop="goods_price" />
                        <el-table-column label="库存" prop="goods_stock" />
                        <el-table-column label="操作" width="200">
                            <template #default="{ row }">
                                <!-- 修改按钮 -->
                                <el-button @click="editProduct(row)" type="text" size="small">修改</el-button>
                                <!-- 删除按钮 -->
                                <el-button @click="deleteProduct(row.goods_id)" type="text" size="small"
                                    style="color: red;">删除</el-button>
                            </template>
                        </el-table-column>
                    </el-table>
                    <el-pagination class="pagination" @current-change="fetchGoods" :current-page="currentPage"
                        :page-size="pageSize" :total="totalGoods" layout="total, prev, pager, next, jumper" />
                </el-card>
            </el-col>
        </el-row>
    </div>

    <!-- 编辑商品弹窗 -->
    <el-dialog title="编辑商品" v-model:visible="dialogVisible" width="50%">
        <el-form :model="productForm" label-width="120px">
            <el-form-item label="商品名称">
                <el-input v-model="productForm.goods_name" placeholder="请输入商品名称" />
            </el-form-item>
            <el-form-item label="商品描述">
                <el-input v-model="productForm.goods_description" placeholder="请输入商品描述" />
            </el-form-item>
            <el-form-item label="价格">
                <el-input v-model="productForm.goods_price" type="number" placeholder="请输入商品价格" />
            </el-form-item>
            <el-form-item label="库存数量">
                <el-input v-model="productForm.goods_stock" type="number" placeholder="请输入库存数量" />
            </el-form-item>
            <el-form-item>
                <el-button type="primary" @click="updateProduct">提交修改</el-button>
                <el-button @click="dialogVisible = false">取消</el-button>
            </el-form-item>
        </el-form>
    </el-dialog>
</template>

<script setup lang="ts">
import { ref } from "vue";
import axios from "axios";
import { ElMessage } from "element-plus";

// 表单数据
const productForm = ref({
    goods_name: "",
    goods_description: "",
    goods_price: 0,
    goods_stock: 0,
    category_id: "",
    supplier_id: "",
    unit_id: "",
});

const dialogVisible = ref(false);
const goodsList = ref([]);
const currentPage = ref(1);
const pageSize = ref(5);
const totalGoods = ref(0);

// 模拟下拉选项（你可以通过接口动态获取）
const categoryOptions = ref([
    { label: "饮料", value: "cat001" },
    { label: "零食", value: "cat002" },
]);

const supplierOptions = ref([
    { label: "供应商A", value: "sup001" },
    { label: "供应商B", value: "sup002" },
]);

const unitOptions = ref([
    { label: "瓶", value: "unit001" },
    { label: "包", value: "unit002" },
]);

// 提交商品
const submitProduct = async () => {
    const form = productForm.value;
    if (!form.goods_name || !form.goods_description || form.goods_price <= 0 || form.goods_stock < 0) {
        ElMessage.error("请填写完整且有效的商品信息");
        return;
    }
    try {
        const res = await axios.post("http://localhost:8080/goods/add", form);
        if (res.status === 200) {
            ElMessage.success("商品添加成功");
            productForm.value = {
                goods_name: "",
                goods_description: "",
                goods_price: 0,
                goods_stock: 0,
                category_id: "",
                supplier_id: "",
                unit_id: "",
            };
            fetchGoods(currentPage.value);
        }
    } catch (err) {
        ElMessage.error("添加失败，请检查网络或服务器");
    }
};

// 获取商品列表
const fetchGoods = async (page: number) => {
    try {
        const res = await axios.post("http://localhost:8080/goods/get", {
            page,
            page_size: pageSize.value,
        });
        if (res.status === 200) {
            goodsList.value = res.data.data || [];
            totalGoods.value = res.data.total || 0;
        }
    } catch (err) {
        ElMessage.error("获取商品列表失败");
    }
};

// 编辑商品
const editProduct = (row: any) => {
    productForm.value = { ...row };
    dialogVisible.value = true;
};

// 更新商品
const updateProduct = async () => {
    try {
        const res = await axios.post("http://localhost:8080/goods/update", productForm.value);
        if (res.status === 200) {
            ElMessage.success("商品更新成功");
            fetchGoods(currentPage.value);
            dialogVisible.value = false;
        }
    } catch (err) {
        ElMessage.error("更新失败，请检查网络或服务器");
    }
};

// 删除商品
const deleteProduct = async (goodsId: string) => {
    try {
        const res = await axios.post("http://localhost:8080/goods/delete", { goods_id: goodsId });
        if (res.status === 200 && res.data.success) {
            ElMessage.success("商品删除成功");
            fetchGoods(currentPage.value);
        } else {
            ElMessage.error("删除商品失败");
        }
    } catch (err) {
        ElMessage.error("删除失败，请检查网络或服务器");
    }
};

// 初始化商品列表
fetchGoods(currentPage.value);
</script>

<style scoped>
.page-container {
    padding: 20px;
}

.pagination {
    margin-top: 16px;
    text-align: right;
}

.el-table .el-button {
    margin-right: 10px;
    /* 给按钮添加右边距，使它们之间有间隔 */
}

/* 修改按钮样式 */
.el-table .el-button--text {
    color: #409EFF;
    /* 设置修改按钮为蓝色 */
}

/* 删除按钮样式 */
.el-table .el-button--text.red-button {
    color: red;
    /* 设置删除按钮为红色 */
}
</style>
