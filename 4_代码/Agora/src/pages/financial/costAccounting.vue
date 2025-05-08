<template>
    <div class="cost-accounting">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="成本项目">
                        <el-input v-model="form.costItem" placeholder="请输入成本项目名称" />
                    </el-form-item>
                    <el-form-item label="金额">
                        <el-input v-model="form.amount" type="number" placeholder="请输入金额" />
                    </el-form-item>
                    <el-form-item label="核算日期">
                        <el-date-picker v-model="form.accountingDate" type="date" placeholder="选择核算日期" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitCostAccounting">确认提交</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    costItem: '',
    amount: '',
    accountingDate: '',
});

const submitCostAccounting = () => {
    console.log('提交成本核算', form.value);
};
</script>

<style scoped>
.cost-accounting {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>