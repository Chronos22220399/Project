<template>
    <div class="sales-ranking">
        <el-card>
            <div class="ranking-area">
                <el-table :data="rankingData">
                    <el-table-column label="排名" prop="rank" />
                    <el-table-column label="商品名称" prop="productName" />
                    <el-table-column label="销售数量" prop="quantity" />
                </el-table>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const rankingData = ref([
    { rank: 1, productName: '商品A', quantity: 1000 },
    { rank: 2, productName: '商品B', quantity: 800 },
    { rank: 3, productName: '商品C', quantity: 600 },
]);

</script>

<style scoped>
.sales-ranking {
    padding: 20px;
}

.ranking-area {
    max-width: 900px;
    margin: 0 auto;
}
</style>