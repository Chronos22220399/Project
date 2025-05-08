<template>
    <el-card>
        <el-form :model="exchange" label-width="120px">
            <el-form-item label="会员姓名">
                <el-input v-model="exchange.name" placeholder="请输入会员姓名" />
            </el-form-item>
            <el-form-item label="兑换商品">
                <el-input v-model="exchange.item" placeholder="如：优惠券、礼品" />
            </el-form-item>
            <el-form-item label="所需积分">
                <el-input v-model="exchange.points" type="number" placeholder="输入积分值" />
            </el-form-item>
            <el-form-item>
                <el-button type="primary" @click="submitExchange">确认兑换</el-button>
            </el-form-item>
        </el-form>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';

const exchange = ref({
    name: '',
    item: '',
    points: ''
});

const submitExchange = () => {
    console.log('积分兑换：', exchange.value);
};
</script>