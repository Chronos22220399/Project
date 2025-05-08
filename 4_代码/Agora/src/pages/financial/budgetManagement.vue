<template>
    <div class="budget-management">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="预算类型">
                        <el-select v-model="form.budgetType" placeholder="请选择预算类型">
                            <el-option label="年度预算" value="annual" />
                            <el-option label="季度预算" value="quarterly" />
                        </el-select>
                    </el-form-item>
                    <el-form-item label="预算金额">
                        <el-input v-model="form.budgetAmount" type="number" placeholder="请输入预算金额" />
                    </el-form-item>
                    <el-form-item label="预算年份">
                        <el-input v-model="form.year" type="number" placeholder="请输入预算年份" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitBudgetManagement">确认提交</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    budgetType: '',
    budgetAmount: '',
    year: '',
});

const submitBudgetManagement = () => {
    console.log('提交预算管理', form.value);
};
</script>

<style scoped>
.budget-management {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>