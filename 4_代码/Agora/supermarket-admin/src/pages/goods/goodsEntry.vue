<template>
    <div>
        <!-- 商品列表部分 -->

        <el-card :body-style="{ padding: '20px' }">
            <h1>商品管理</h1>
            <h2>商品列表</h2>
            <el-button @click="fetchGoods" type="primary">获取商品列表</el-button>
            <div v-if="goodsList.length > 0">
                <el-table :data="goodsList" style="width: 100%" border>
                    <el-table-column label="商品ID" prop="goods_id"></el-table-column>
                    <el-table-column label="商品名称" prop="goods_name"></el-table-column>
                    <el-table-column label="分类名称" prop="category_name"></el-table-column>
                    <el-table-column label="库存" prop="stock"></el-table-column>
                    <el-table-column label="供应商" prop="external_info.supplier_code"></el-table-column>
                    <el-table-column label="仓库" prop="external_info.warehouse_code"></el-table-column>
                </el-table>
            </div>
            <div v-else>
                <p>没有商品数据</p>
            </div>
        </el-card>

        <!-- 创建商品部分 -->
        <el-card :body-style="{ padding: '20px' }" class="mt-4">
            <h2>创建商品</h2>
            <el-form :model="product" ref="productForm" label-width="120px">
                <el-form-item label="商品名称" required>
                    <el-input v-model="product.goods_name" placeholder="请输入商品名称"></el-input>
                </el-form-item>
                <el-form-item label="分类ID" required>
                    <el-select v-model="product.category_id" placeholder="请选择分类">
                        <el-option label="CAT001" value="CAT001" />
                        <el-option label="CAT002" value="CAT002" />
                        <el-option label="CAT003" value="CAT003" />
                    </el-select>
                </el-form-item>
                <el-form-item label="供应商ID" required>
                    <el-select v-model="product.supplier_id" placeholder="请选择供应商">
                        <el-option label="SUP001" value="SUP001" />
                        <el-option label="SUP002" value="SUP002" />
                        <el-option label="SUP003" value="SUP003" />
                    </el-select>
                </el-form-item>
                <el-form-item label="单位ID" required>
                    <el-select v-model="product.unit_id" placeholder="请选择单位">
                        <el-option label="UNIT001" value="UNIT001" />
                        <el-option label="UNIT002" value="UNIT002" />
                        <el-option label="UNIT003" value="UNIT003" />
                    </el-select>
                </el-form-item>
                <el-form-item label="保质期天数" required>
                    <el-input-number v-model="product.shelf_life_days" :min="0"
                        placeholder="请输入保质期天数"></el-input-number>
                </el-form-item>
                <el-form-item label="条形码" required>
                    <el-input v-model="product.barcode" placeholder="请输入商品条形码"></el-input>
                </el-form-item>
                <el-form-item label="商品图片URL" required>
                    <el-input v-model="product.image_url" placeholder="请输入商品图片URL"></el-input>
                </el-form-item>
                <el-form-item label="商品描述" required>
                    <el-input type="textarea" v-model="product.description" placeholder="请输入商品描述" rows="4"></el-input>
                </el-form-item>
                <el-button type="primary" @click="createProduct">创建商品</el-button>
            </el-form>
        </el-card>

        <!-- 商品详情部分 -->
        <el-card :body-style="{ padding: '20px' }" class="mt-4">
            <h2>商品详情</h2>
            <el-form :model="productDetail" ref="productDetailForm" label-width="120px">
                <el-form-item label="商品ID" required>
                    <el-select v-model="goods_id" placeholder="请选择商品">
                        <el-option v-for="item in goodsList" :key="item.goods_id" :label="item.goods_id"
                            :value="item.goods_id" />
                    </el-select>
                </el-form-item>
                <el-button type="primary" @click="getProductDetails">获取商品详情</el-button>

                <div v-if="productDetail">
                    <el-form-item label="商品名称">
                        <span>{{ productDetail.goods_name }}</span>
                    </el-form-item>
                    <el-form-item label="库存">
                        <span>{{ productDetail.quantity }}</span>
                    </el-form-item>
                    <el-form-item label="单位">
                        <span>{{ productDetail.unit }}</span>
                    </el-form-item>
                    <el-form-item label="仓库名称">
                        <span>{{ productDetail.warehouse_name }}</span>
                    </el-form-item>
                    <el-form-item label="位置">
                        <span>{{ productDetail.location }}</span>
                    </el-form-item>
                    <el-form-item label="保质期">
                        <span>{{ productDetail.shelf_life_days }} 天</span>
                    </el-form-item>
                </div>
            </el-form>
        </el-card>
    </div>
</template>


<script lang="ts">
import { defineComponent, ref } from 'vue';
import axios from 'axios';

export default defineComponent({
    name: 'GoodsManager',
    setup() {
        const goodsList = ref < any[] > ([{
            goods_id: 1,
            goods_name: "可乐",
            category_name: "饮料",
            stock: 100,
            external_info: {
                supplier_code: "SUP001",
                warehouse_code: "WH001",
            },
        },
        {
            goods_id: 2,
            goods_name: "饼干",
            category_name: "零食",
            stock: 50,
            external_info: {
                supplier_code: "SUP002",
                warehouse_code: "WH002",
            },
        },
        {
            goods_id: 3,
            goods_name: "水果",
            category_name: "生鲜",
            stock: 30,
            external_info: {
                supplier_code: "SUP003",
                warehouse_code: "WH003",
            },
        },
        ]);
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
        const goods_id = ref('');
        const productDetail = ref < any > (null);

        // 获取商品列表的请求
        const fetchGoods = async () => {
            try {
                const response = await axios.post('http://localhost:8080/api/goods/get_by_page', {
                    page: 1,       // 当前页码，默认1
                    page_size: 10, // 每页商品数量，默认10
                });

                // 更新商品列表
                if (response.data.code === 200) {
                    goodsList.value = response.data.data.items;
                }
            } catch (error) {
                console.error('Error fetching goods:', error);
            }
        };

        // 创建商品的请求
        const createProduct = async () => {
            try {
                const response = await axios.post('http://localhost:8080/api/goods/create', {
                    goods_name: product.value.goods_name,
                    category_id: product.value.category_id,
                    supplier_id: product.value.supplier_id,
                    unit_id: product.value.unit_id,
                    shelf_life_days: product.value.shelf_life_days,
                    barcode: product.value.barcode,
                    image_url: product.value.image_url,
                    description: product.value.description,
                });

                if (response.data.code === 201) {
                    console.log('商品创建成功:', response.data);
                } else {
                    console.log('创建失败:', response.data.error);
                }
            } catch (error) {
                console.error('Error creating product:', error);
            }
        };

        // 获取商品详细信息的请求
        const getProductDetails = async () => {
            try {
                const response = await axios.post('http://localhost:8080/api/goods/get_goods_detail_info', {
                    goods_id: goods_id.value,
                });

                if (response.data.code === 200) {
                    productDetail.value = response.data.data;
                } else {
                    console.log('商品详细信息获取失败:', response.data.error);
                }
            } catch (error) {
                console.error('Error fetching product details:', error);
            }
        };

        return {
            goodsList,
            product,
            goods_id,
            productDetail,
            fetchGoods,
            createProduct,
            getProductDetails,
        };
    },
});
</script>

<style scoped>
.el-card {
    margin-bottom: 20px;
}

.mt-4 {
    margin-top: 20px;
}

h2 {
    margin-bottom: 10px;
}

.el-button {
    margin-top: 10px;
}
</style>