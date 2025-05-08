<template>
    <el-card>
        <el-table :data="salaryList">
            <el-table-column label="员工姓名" prop="name" />
            <el-table-column label="基本工资" prop="base" />
            <el-table-column label="奖金" prop="bonus" />
            <el-table-column label="总工资" prop="total" />
        </el-table>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';
const salaryList = ref([
    { name: '李四', base: 5000, bonus: 1000, total: 6000 }
]);
</script>