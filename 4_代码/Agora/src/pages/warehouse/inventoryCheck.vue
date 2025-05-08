<template>
    <div class="inventory-check">
        <el-card>
            <div class="header">
                <el-button type="primary" @click="startInventoryCheck">开始盘点</el-button>
            </div>
            <el-table :data="inventoryList" style="width: 100%; margin-top: 20px;">
                <el-table-column prop="productName" label="商品名称" />
                <el-table-column prop="currentStock" label="当前库存" />
                <el-table-column prop="lastChecked" label="上次盘点时间" />
            </el-table>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const inventoryList = ref([
    { productName: "商品A", currentStock: 120, lastChecked: "2025-04-01" },
    { productName: "商品B", currentStock: 50, lastChecked: "2025-04-01" },
]);

const startInventoryCheck = () => {
    console.log("开始库存盘点");
};
</script>

<style scoped>
.inventory-check {
    padding: 20px;
}

.header {
    display: flex;
    justify-content: flex-end;
}
</style>