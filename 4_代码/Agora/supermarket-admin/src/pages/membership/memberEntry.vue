<template>
    <el-card>
        <el-form :model="form" label-width="120px">
            <el-form-item label="会员姓名">
                <el-input v-model="form.name" placeholder="请输入会员姓名" />
            </el-form-item>
            <el-form-item label="联系方式">
                <el-input v-model="form.phone" placeholder="请输入联系电话" />
            </el-form-item>
            <el-form-item label="注册日期">
                <el-date-picker v-model="form.date" type="date" placeholder="选择日期" />
            </el-form-item>
            <el-form-item label="会员等级">
                <el-select v-model="form.level" placeholder="选择等级">
                    <el-option label="普通会员" value="normal" />
                    <el-option label="黄金会员" value="gold" />
                    <el-option label="钻石会员" value="diamond" />
                </el-select>
            </el-form-item>
            <el-form-item>
                <el-button type="primary" @click="submit">提交</el-button>
            </el-form-item>
        </el-form>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    name: '',
    phone: '',
    date: '',
    level: ''
});

const submit = () => {
    console.log('会员信息提交：', form.value);
};
</script>