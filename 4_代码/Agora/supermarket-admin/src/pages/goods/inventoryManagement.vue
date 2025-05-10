<template>
    <div class="page-container">
        <h2>商品库存管理</h2>

        <!-- 添加商品表单 -->
        <div class="form-card">
            <div class="form-row">
                <el-input v-model="newName" placeholder="商品名称" style="width: 200px; margin-right: 10px" />
                <el-input-number v-model="newStock" :min="0" placeholder="库存数量" style="margin-right: 10px" />
                <el-button type="primary" @click="addProduct">添加商品</el-button>
            </div>
        </div>

        <!-- 库存表格 -->
        <el-table :data="paginatedInventory" border style="width: 100%; margin-top: 20px">
            <el-table-column prop="name" label="商品名称"></el-table-column>
            <el-table-column prop="stock" label="库存数量"></el-table-column>
            <el-table-column label="操作" width="300">
                <template #default="{ row }">
                    <el-input-number v-model="row.stock" :min="0" @change="updateStock(row)"
                        style="margin-right: 10px" />
                    <el-button type="danger" size="small" @click="deleteProduct(row)">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <!-- 分页器 -->
        <el-pagination class="mt-4" layout="total, sizes, prev, pager, next, jumper" :total="inventory.length"
            :current-page="currentPage" :page-size="pageSize" @size-change="handleSizeChange"
            @current-change="handlePageChange" />
    </div>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue';
import { ElMessage } from 'element-plus';

// 假数据
const inventory = ref([
    { name: '可乐', stock: 100 },
    { name: '饼干', stock: 50 },
    { name: '水果', stock: 30 },
    { name: '牛奶', stock: 200 },
    { name: '面包', stock: 150 },
    { name: '巧克力', stock: 80 },
    { name: '水', stock: 300 },
    { name: '洗发水', stock: 50 },
    { name: '牙膏', stock: 120 },
    { name: '纸巾', stock: 90 },
    { name: '鸡蛋', stock: 200 },
    { name: '苹果', stock: 70 },
    { name: '橙子', stock: 60 },
    { name: '葡萄', stock: 110 },
    { name: '西瓜', stock: 180 },
]);

const currentPage = ref(1);
const pageSize = ref(5);
const newName = ref('');
const newStock = ref(0);

// 获取分页数据
const paginatedInventory = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value;
    const end = currentPage.value * pageSize.value;
    return inventory.value.slice(start, end);
});

// 添加商品
const addProduct = () => {
    if (!newName.value.trim()) {
        ElMessage.warning('商品名称不能为空');
        return;
    }
    if (inventory.value.some(item => item.name === newName.value.trim())) {
        ElMessage.error('该商品已存在');
        return;
    }
    inventory.value.push({
        name: newName.value.trim(),
        stock: newStock.value
    });
    ElMessage.success(`添加成功：${newName.value}`);
    newName.value = '';
    newStock.value = 0;
};

// 更新库存
const updateStock = (row: { name: string; stock: number }) => {
    ElMessage.success(`库存更新成功: ${row.name} 库存为 ${row.stock}`);
};

// 删除商品
const deleteProduct = (row: { name: string }) => {
    inventory.value = inventory.value.filter(item => item.name !== row.name);
    ElMessage.success(`已删除商品：${row.name}`);
};

// 分页改变每页条数
const handleSizeChange = (val: number) => {
    pageSize.value = val;
    currentPage.value = 1; // 每次改变每页条数时，回到第一页
};

// 分页改变当前页
const handlePageChange = (val: number) => {
    currentPage.value = val;
};
</script>

<style scoped>
.page-container {
    padding: 20px;
    background-color: #ffffff;
    border-radius: 8px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
}

.form-card {
    background-color: #ffffff;
    padding: 16px;
    border-radius: 8px;
    box-shadow: 0 2px 6px rgba(0, 0, 0, 0.05);
    margin-bottom: 16px;
}

.form-row {
    display: flex;
    align-items: center;
}

.mt-4 {
    margin-top: 20px;
}
</style>
