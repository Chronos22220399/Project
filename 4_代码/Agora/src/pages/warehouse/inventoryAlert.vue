<template>
    <div class="inventory-alert">
        <el-card>
            <h3>库存报警列表</h3>
            <el-table :data="alertList" style="width: 100%; margin-top: 20px;">
                <el-table-column prop="productName" label="商品名称" />
                <el-table-column prop="currentStock" label="当前库存" />
                <el-table-column prop="threshold" label="报警阈值" />
            </el-table>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const alertList = ref([
    { productName: "商品A", currentStock: 10, threshold: 20 },
    { productName: "商品C", currentStock: 5, threshold: 15 },
]);
</script>

<style scoped>
.inventory-alert {
    padding: 20px;
}
</style>