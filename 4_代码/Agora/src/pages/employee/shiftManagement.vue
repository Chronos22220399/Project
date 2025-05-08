<template>
    <el-card>
        <el-select v-model="selectedEmployee" placeholder="选择员工">
            <el-option label="张三" value="zhangsan" />
        </el-select>
        <el-date-picker v-model="scheduleDate" type="date" placeholder="选择排班日期" />
        <el-time-picker v-model="startTime" placeholder="上班时间" />
        <el-time-picker v-model="endTime" placeholder="下班时间" />
        <el-button type="primary" @click="submitSchedule">提交排班</el-button>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';
const selectedEmployee = ref('');
const scheduleDate = ref('');
const startTime = ref('');
const endTime = ref('');
const submitSchedule = () => { };
</script>