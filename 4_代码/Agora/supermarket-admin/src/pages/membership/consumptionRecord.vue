<template>
    <el-card>
        <el-table :data="records" border>
            <el-table-column label="会员姓名" prop="name" />
            <el-table-column label="消费时间" prop="date" />
            <el-table-column label="消费金额" prop="amount" />
            <el-table-column label="获得积分" prop="points" />
        </el-table>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';

const records = ref([
    { name: '张三', date: '2024-12-01', amount: 150, points: 15 },
    { name: '李四', date: '2024-12-03', amount: 300, points: 30 }
]);
</script>