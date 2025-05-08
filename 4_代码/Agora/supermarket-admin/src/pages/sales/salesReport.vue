<template>
    <div class="sales-report">
        <el-card>
            <div class="report-area">
                <el-table :data="reportData">
                    <el-table-column label="商品名称" prop="productName" />
                    <el-table-column label="销售数量" prop="quantity" />
                    <el-table-column label="销售金额" prop="amount" />
                </el-table>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const reportData = ref([
    { productName: '商品A', quantity: 100, amount: 5000 },
    { productName: '商品B', quantity: 200, amount: 10000 },
]);

</script>

<style scoped>
.sales-report {
    padding: 20px;
}

.report-area {
    max-width: 900px;
    margin: 0 auto;
}
</style>