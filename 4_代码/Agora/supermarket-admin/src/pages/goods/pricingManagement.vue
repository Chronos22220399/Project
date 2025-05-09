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
            <ul class="price-list">
                <li v-for="item in goodsPrices.items" :key="item.goods_price_id" class="price-item">
                    <div>
                        <p><strong>商品ID:</strong> {{ item.goods_id }}</p>
                        <p><strong>价格:</strong> ¥{{ item.price }}</p>
                        <p><strong>生效时间:</strong> {{ item.start_time }}</p>
                        <p><strong>备注:</strong> {{ item.note || '—' }}</p>
                    </div>
                    <div class="actions">
                        <button @click="editPrice(item)">修改</button>
                        <button class="danger" @click="deletePrice(item.goods_price_id)">删除</button>
                    </div>
                </li>
            </ul>

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
import axios from 'axios';

export default {
    data() {
        return {
            goodsId: '',
            price: '',
            startTime: '',
            note: '',
            goodsPrices: {
                items: [],
                page: 1,
                page_size: 10,
                total: 0
            }
        };
    },
    methods: {
        async createPrice() {
            try {
                const response = await axios.post('/api/goods_price/create', {
                    goods_id: this.goodsId,
                    price: this.price,
                    start_time: this.startTime,
                    note: this.note
                });
                if (response.data.code === 200) {
                    alert('商品价格创建成功');
                    this.clearForm();
                    this.loadGoodsPrices();
                } else {
                    alert('创建失败');
                }
            } catch (error) {
                console.error('请求失败', error);
            }
        },

        async deletePrice(goodsPriceId) {
            try {
                const response = await axios.post('/api/goods_price/remove', {
                    goods_id: goodsPriceId
                });
                if (response.data.code === 200) {
                    alert('商品价格删除成功');
                    this.loadGoodsPrices();
                } else {
                    alert('删除失败');
                }
            } catch (error) {
                console.error('请求失败', error);
            }
        },

        async loadGoodsPrices() {
            try {
                const response = await axios.post('/api/goods_price/get_by_page', {
                    page: this.goodsPrices.page,
                    page_size: this.goodsPrices.page_size
                });
                if (response.data.code === 200) {
                    this.goodsPrices = response.data.data;
                } else {
                    alert('加载商品价格失败');
                }
            } catch (error) {
                console.error('请求失败', error);
            }
        },

        nextPage() {
            if (this.goodsPrices.page * this.goodsPrices.page_size < this.goodsPrices.total) {
                this.goodsPrices.page += 1;
                this.loadGoodsPrices();
            }
        },

        prevPage() {
            if (this.goodsPrices.page > 1) {
                this.goodsPrices.page -= 1;
                this.loadGoodsPrices();
            }
        },

        clearForm() {
            this.goodsId = '';
            this.price = '';
            this.startTime = '';
            this.note = '';
        },

        editPrice(item) {
            alert('修改功能未实现，可拓展为弹窗编辑');
        }
    },
    mounted() {
        this.loadGoodsPrices();
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

.price-list {
    list-style: none;
    padding: 0;
    margin: 0;
}

.price-item {
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
    padding: 15px;
    border-bottom: 1px solid #eee;
    transition: background-color 0.2s;
}

.price-item:hover {
    background-color: #f9f9f9;
}

.price-item p {
    margin: 4px 0;
    font-size: 14px;
}

.actions {
    display: flex;
    gap: 10px;
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
</style>
