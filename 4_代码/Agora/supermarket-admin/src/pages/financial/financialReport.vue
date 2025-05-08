<template>
    <div class="financial-report">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="报表类型">
                        <el-select v-model="form.reportType" placeholder="请选择报表类型">
                            <el-option label="月度报表" value="monthly" />
                            <el-option label="年度报表" value="annual" />
                        </el-select>
                    </el-form-item>
                    <el-form-item label="报表年份">
                        <el-input v-model="form.year" type="number" placeholder="请输入报表年份" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="generateReport">生成报表</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    reportType: '',
    year: '',
});

const generateReport = () => {
    console.log('生成财务报表', form.value);
};
</script>

<style scoped>
.financial-report {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>