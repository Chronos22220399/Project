<template>
    <el-card>
        <el-table :data="attendanceData">
            <el-table-column label="员工" prop="name" />
            <el-table-column label="日期" prop="date" />
            <el-table-column label="签到时间" prop="checkIn" />
            <el-table-column label="签退时间" prop="checkOut" />
        </el-table>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';
const attendanceData = ref([
    { name: '张三', date: '2025-05-01', checkIn: '09:00', checkOut: '17:00' }
]);
</script>