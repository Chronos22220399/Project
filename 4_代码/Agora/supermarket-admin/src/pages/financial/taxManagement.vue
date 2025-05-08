<template>
    <div class="tax-management">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="税务类型">
                        <el-select v-model="form.taxType" placeholder="请选择税务类型">
                            <el-option label="增值税" value="vat" />
                            <el-option label="所得税" value="income" />
                        </el-select>
                    </el-form-item>
                    <el-form-item label="税率">
                        <el-input v-model="form.taxRate" type="number" placeholder="请输入税率" />
                    </el-form-item>
                    <el-form-item label="纳税日期">
                        <el-date-picker v-model="form.taxDate" type="date" placeholder="选择纳税日期" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitTaxManagement">确认提交</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    taxType: '',
    taxRate: '',
    taxDate: '',
});

const submitTaxManagement = () => {
    console.log('提交税务管理', form.value);
};
</script>

<style scoped>
.tax-management {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>