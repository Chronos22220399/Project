<template>
    <div class="supplier-evaluation">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="供应商名称">
                        <el-input v-model="form.supplierName" placeholder="请输入供应商名称" />
                    </el-form-item>
                    <el-form-item label="评价内容">
                        <el-input v-model="form.evaluation" type="textarea" placeholder="请输入评价内容" />
                    </el-form-item>
                    <el-form-item label="评分">
                        <el-rate v-model="form.rating" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitEvaluation">确认提交</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    supplierName: '',
    evaluation: '',
    rating: 3,
});

const submitEvaluation = () => {
    console.log('提交供应商评价', form.value);
};
</script>

<style scoped>
.supplier-evaluation {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>