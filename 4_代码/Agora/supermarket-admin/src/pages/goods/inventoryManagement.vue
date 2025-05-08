<template>
    <div class="page-container">
        <h2>商品库存管理</h2>
        <el-table :data="inventory" border style="width: 100%">
            <el-table-column prop="name" label="商品名称"></el-table-column>
            <el-table-column prop="stock" label="库存数量"></el-table-column>
            <el-table-column label="操作">
                <template #default="{ row }">
                    <el-input-number v-model="row.stock" :min="0" @change="updateStock(row)" />
                </template>
            </el-table-column>
        </el-table>
    </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { ElMessage } from "element-plus";

const inventory = ref([
    { name: "可乐", stock: 100 },
    { name: "饼干", stock: 50 },
    { name: "水果", stock: 30 },
]);

const updateStock = (row: { name: string; stock: number }) => {
    ElMessage.success(`库存更新成功: ${row.name} 库存为 ${row.stock}`);
};
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
</style>