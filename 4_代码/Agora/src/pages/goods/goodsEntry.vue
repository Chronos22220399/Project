<template>
    <div class="page-container">
        <h2>商品信息录入</h2>
        <!-- 商品录入表单 -->
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
            <el-form-item>
                <el-button type="primary" @click="submitProduct">提交</el-button>
            </el-form-item>
        </el-form>

        <!-- 商品列表展示 -->
        <h3>商品列表</h3>
        <el-table :data="goodsList" style="width: 100%">
            <el-table-column label="商品ID" prop="goods_id"></el-table-column>
            <el-table-column label="商品名称" prop="goods_name"></el-table-column>
            <el-table-column label="价格" prop="goods_price"></el-table-column>
            <el-table-column label="库存" prop="goods_stock"></el-table-column>
        </el-table>

        <!-- 分页控制 -->
        <el-pagination @current-change="fetchGoods" :current-page="currentPage" :page-size="pageSize"
            :total="totalGoods" layout="total, prev, pager, next, jumper">
        </el-pagination>
    </div>
</template>

<script setup lang="ts">
import axios from "axios";
import { ref } from "vue";
import { ElMessage } from "element-plus";

// 商品录入表单数据
const productForm = ref({
    goods_name: "",
    goods_description: "",
    goods_price: 0,
    goods_stock: 0,
});

// 商品列表数据、分页参数
const goodsList = ref([]);
const currentPage = ref(1);
const pageSize = ref(5);  // 每页显示 5 条商品
const totalGoods = ref(0);

// 提交商品信息
const submitProduct = async () => {
    const { goods_name, goods_description, goods_price, goods_stock } = productForm.value;

    // 校验表单
    if (!goods_name || !goods_description || goods_price <= 0 || goods_stock < 0) {
        ElMessage.error("请完整填写商品信息, 价格需大于0, 库存不能为负");
        return;
    }

    try {
        const response = await axios.post("http://localhost:8888/goods/add", {
            goods_name,
            goods_description,
            goods_price,
            goods_stock,
        });

        if (response.status === 200) {
            ElMessage.success("商品信息已成功提交！");
            // 重置表单
            productForm.value = {
                goods_name: "",
                goods_description: "",
                goods_price: 0,
                goods_stock: 0,
            };
            // 提交成功后刷新商品列表
            fetchGoods(currentPage.value);
        } else {
            ElMessage.error("提交失败，请稍后重试！");
        }
    } catch (error) {
        ElMessage.error("提交出错，请检查服务器连接！");
        console.error(error);
    }
};

// 获取商品列表数据
const fetchGoods = async (page: number) => {
    try {
        const response = await axios.post("http://localhost:8888/goods/get", {
            page: page,
            page_size: pageSize.value,
        });

        if (response.status === 200) {
            const data = response.data;
            goodsList.value = data.data || [];
            totalGoods.value = data.total || 0;
        } else {
            ElMessage.error("获取商品列表失败，请稍后重试！");
        }
    } catch (error) {
        ElMessage.error("获取商品列表失败，请检查服务器连接！");
        console.error(error);
    }
};

// 初次加载商品数据
fetchGoods(currentPage.value);
</script>

<style scoped>
.page-container {
    padding: 20px;
    background-color: #f5f5f5;
    /* 背景色 */
    border-radius: 8px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    /* 添加阴影 */
}

.el-table {
    margin-top: 20px;
}
</style>
