<template>
    <div class="cashier-management">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="收银员">
                        <el-input v-model="form.cashier" placeholder="请输入收银员姓名" />
                    </el-form-item>
                    <el-form-item label="交易金额">
                        <el-input v-model="form.amount" type="number" placeholder="请输入交易金额" />
                    </el-form-item>
                    <el-form-item label="交易时间">
                        <el-date-picker v-model="form.transactionDate" type="datetime" placeholder="选择交易时间" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitCashierManagement">确认提交</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    cashier: '',
    amount: '',
    transactionDate: '',
});

const submitCashierManagement = () => {
    console.log('收银管理提交', form.value);
};
</script>

<style scoped>
.cashier-management {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>