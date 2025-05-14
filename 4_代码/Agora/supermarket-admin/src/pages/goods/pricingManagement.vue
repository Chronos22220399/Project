<template>
    <div class="goods-price-manager">
        <h1>商品价格管理</h1>

        <!-- 商品价格创建 -->
        <div class="card">
            <h2>创建商品价格</h2>
            <div class="form-grid">
                <input v-model="goodsId" placeholder="商品ID" />
                <input v-model="price" type="number" step="0.01" placeholder="价格" />
                <input v-model="startTime" placeholder="生效时间 (ISO8601格式)" />
                <input v-model="note" placeholder="备注" />
                <button class="primary" @click="createPrice">创建价格</button>
            </div>
        </div>

        <!-- 商品价格列表 -->
        <div class="card">
            <h2>商品价格列表</h2>
            <table class="price-table">
                <thead>
                    <tr>
                        <th>商品ID</th>
                        <th>价格 (¥)</th>
                        <th>生效时间</th>
                        <th>备注</th>
                        <th>操作</th>
                    </tr>
                </thead>
                <tbody>
                    <tr v-for="item in goodsPrices.items" :key="item.goods_price_id">
                        <td>{{ item.goods_id }}</td>
                        <td>{{ item.price }}</td>
                        <td>{{ item.start_time }}</td>
                        <td>{{ item.note || '—' }}</td>
                        <td>
                            <el-button size="mini" type="text" @click="editPrice(scope.row)">编辑</el-button>
                            <el-button size="mini" type="danger" class="red-button"
                                @click="deletePrice(scope.row.price_id)">删除</el-button>
                        </td>
                    </tr>
                </tbody>
            </table>

            <!-- 分页控制 -->
            <div class="pagination" v-if="goodsPrices.total > goodsPrices.page_size">
                <button @click="prevPage" :disabled="goodsPrices.page === 1">上一页</button>
                <span>第 {{ goodsPrices.page }} 页</span>
                <button @click="nextPage"
                    :disabled="goodsPrices.page * goodsPrices.page_size >= goodsPrices.total">下一页</button>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    data() {
        return {
            goodsId: '',
            price: '',
            startTime: '',
            note: '',
            goodsPrices: {
                page: 1,
                page_size: 10,
                total: 50, // 模拟50条数据
                items: []
            }
        };
    },
    created() {
        this.loadPageData();
    },
    methods: {
        createPrice() {
            alert('创建商品价格功能尚未实现');
        },

        deletePrice(goodsPriceId) {
            alert('删除商品价格功能尚未实现');
        },

        nextPage() {
            if (this.goodsPrices.page * this.goodsPrices.page_size < this.goodsPrices.total) {
                this.goodsPrices.page += 1;
                this.loadPageData();
            }
        },

        prevPage() {
            if (this.goodsPrices.page > 1) {
                this.goodsPrices.page -= 1;
                this.loadPageData();
            }
        },

        loadPageData() {
            const { page, page_size } = this.goodsPrices;
            const start = (page - 1) * page_size;
            const end = start + page_size;

            const allItems = Array.from({ length: this.goodsPrices.total }, (_, index) => {
                const id = 1001 + index;
                return {
                    goods_price_id: index + 1,
                    goods_id: id.toString(),
                    price: (Math.random() * 200 + 50).toFixed(2),
                    start_time: new Date(Date.now() - Math.random() * 1e10).toISOString(),
                    note: ['促销价', '限时优惠', '特价', '新品上市', ''][Math.floor(Math.random() * 5)]
                };
            });

            this.goodsPrices.items = allItems.slice(start, end);
        }
    }
};
</script>

<style scoped>
.goods-price-manager {
    padding: 20px;
    font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif;
}

h1 {
    font-size: 24px;
    margin-bottom: 20px;
    color: #333;
}

.card {
    background-color: #fff;
    border-radius: 10px;
    padding: 20px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.05);
    margin-bottom: 20px;
}

h2 {
    font-size: 20px;
    margin-bottom: 15px;
    color: #444;
}

.form-grid {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
    gap: 12px;
    margin-bottom: 15px;
}

.form-grid input {
    padding: 8px 10px;
    border: 1px solid #ccc;
    border-radius: 6px;
    font-size: 14px;
    width: 100%;
    box-sizing: border-box;
}

button {
    padding: 8px 14px;
    font-size: 14px;
    border: none;
    border-radius: 6px;
    cursor: pointer;
    transition: all 0.2s ease;
}

button.primary {
    background-color: #409EFF;
    color: white;
}

button.primary:hover {
    background-color: #66b1ff;
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

.pagination {
    display: flex;
    justify-content: flex-end;
    align-items: center;
    gap: 12px;
    margin-top: 16px;
}

.pagination button {
    background-color: #f2f2f2;
    color: #333;
}

.pagination button:disabled {
    opacity: 0.6;
    cursor: not-allowed;
}

/* 表格样式 */
.price-table {
    width: 100%;
    border-collapse: collapse;
    margin-top: 10px;
    font-size: 14px;
}

.price-table th,
.price-table td {
    padding: 12px;
    border-bottom: 1px solid #eee;
    text-align: left;
}

.price-table th {
    background-color: #f5f7fa;
    color: #333;
    font-weight: 600;
}

.price-table tr:hover {
    background-color: #f9f9f9;
}
</style>
