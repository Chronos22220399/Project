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
                            <button @click="editPrice(item)">修改</button>
                            <button class="danger" @click="deletePrice(item.goods_price_id)">删除</button>
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
                total: 15,  // 总共有15条数据，方便分页
                items: [
                    { goods_price_id: 1, goods_id: '1001', price: 49.99, start_time: '2025-05-01T08:00:00Z', note: '促销价' },
                    { goods_price_id: 2, goods_id: '1002', price: 89.5, start_time: '2025-05-03T12:00:00Z', note: '' },
                    { goods_price_id: 3, goods_id: '1003', price: 120.0, start_time: '2025-05-05T00:00:00Z', note: '新品上市' },
                    { goods_price_id: 4, goods_id: '1004', price: 59.99, start_time: '2025-05-07T14:00:00Z', note: '特价' },
                    { goods_price_id: 5, goods_id: '1005', price: 99.99, start_time: '2025-05-10T09:30:00Z', note: '促销价' },
                    { goods_price_id: 6, goods_id: '1006', price: 149.5, start_time: '2025-05-12T16:45:00Z', note: '' },
                    { goods_price_id: 7, goods_id: '1007', price: 180.0, start_time: '2025-05-15T08:00:00Z', note: '限时折扣' },
                    { goods_price_id: 8, goods_id: '1008', price: 220.5, start_time: '2025-05-18T10:00:00Z', note: '特价' },
                    { goods_price_id: 9, goods_id: '1009', price: 79.99, start_time: '2025-05-20T08:30:00Z', note: '新品促销' },
                    { goods_price_id: 10, goods_id: '1010', price: 119.0, start_time: '2025-05-22T12:00:00Z', note: '限时优惠' },
                    { goods_price_id: 11, goods_id: '1011', price: 89.99, start_time: '2025-05-24T14:15:00Z', note: '' },
                    { goods_price_id: 12, goods_id: '1012', price: 129.0, start_time: '2025-05-26T16:30:00Z', note: '优惠价' },
                    { goods_price_id: 13, goods_id: '1013', price: 99.99, start_time: '2025-05-28T18:00:00Z', note: '新商品' },
                    { goods_price_id: 14, goods_id: '1014', price: 169.99, start_time: '2025-05-30T09:00:00Z', note: '季末清仓' },
                    { goods_price_id: 15, goods_id: '1015', price: 75.0, start_time: '2025-06-01T10:30:00Z', note: '' }
                ]
            }
        };
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
            }
        },

        prevPage() {
            if (this.goodsPrices.page > 1) {
                this.goodsPrices.page -= 1;
            }
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

button.danger {
    background-color: #f56c6c;
    color: white;
}

button.danger:hover {
    background-color: #ff7b7b;
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
