<template>
    <el-card>
        <el-table :data="levels" border>
            <el-table-column label="等级名称" prop="name" />
            <el-table-column label="所需积分" prop="points" />
            <el-table-column label="专属优惠" prop="benefits" />
        </el-table>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';

const levels = ref([
    { name: '普通会员', points: 0, benefits: '无' },
    { name: '黄金会员', points: 1000, benefits: '95折' },
    { name: '钻石会员', points: 3000, benefits: '9折+专属客服' }
]);
</script>