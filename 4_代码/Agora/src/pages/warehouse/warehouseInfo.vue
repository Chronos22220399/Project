<template>
    <div class="warehouse-info">
        <el-card>
            <div class="header">
                <el-button type="primary" @click="addWarehouse">新增仓库</el-button>
            </div>
            <el-table :data="warehouseList" style="width: 100%; margin-top: 20px;">
                <el-table-column prop="name" label="仓库名称" />
                <el-table-column prop="location" label="仓库位置" />
                <el-table-column prop="manager" label="负责人" />
                <el-table-column prop="capacity" label="仓库容量" />
            </el-table>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const warehouseList = ref([
    { name: "主仓库", location: "武汉", manager: "张三", capacity: "5000件" },
    { name: "分仓库A", location: "广州", manager: "李四", capacity: "2000件" },
]);

const addWarehouse = () => {
    console.log("点击新增仓库");
};
</script>

<style scoped>
.warehouse-info {
    padding: 20px;
}

.header {
    display: flex;
    justify-content: flex-end;
}
</style>