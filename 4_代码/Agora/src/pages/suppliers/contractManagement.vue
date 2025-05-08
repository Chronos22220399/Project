<template>
    <div class="contract-management">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="合同编号">
                        <el-input v-model="form.contractNumber" placeholder="请输入合同编号" />
                    </el-form-item>
                    <el-form-item label="供应商名称">
                        <el-input v-model="form.supplierName" placeholder="请输入供应商名称" />
                    </el-form-item>
                    <el-form-item label="合同金额">
                        <el-input v-model="form.contractAmount" type="number" placeholder="请输入合同金额" />
                    </el-form-item>
                    <el-form-item label="签订日期">
                        <el-date-picker v-model="form.contractDate" type="date" placeholder="选择签订日期" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitContract">确认提交</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    contractNumber: '',
    supplierName: '',
    contractAmount: '',
    contractDate: '',
});

const submitContract = () => {
    console.log('提交合同信息', form.value);
};
</script>

<style scoped>
.contract-management {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>