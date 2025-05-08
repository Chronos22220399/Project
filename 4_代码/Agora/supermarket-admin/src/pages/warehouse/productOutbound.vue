<template>
    <div class="product-outbound">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="100px">
                    <el-form-item label="商品名称">
                        <el-input v-model="form.productName" placeholder="请输入商品名称" />
                    </el-form-item>
                    <el-form-item label="数量">
                        <el-input v-model="form.quantity" type="number" placeholder="请输入数量" />
                    </el-form-item>
                    <el-form-item label="出库仓库">
                        <el-select v-model="form.warehouse" placeholder="请选择仓库">
                            <el-option label="主仓库" value="主仓库" />
                            <el-option label="分仓库A" value="分仓库A" />
                        </el-select>
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitOutbound">确认出库</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    productName: '',
    quantity: '',
    warehouse: '',
});

const submitOutbound = () => {
    console.log('提交出库', form.value);
};
</script>

<style scoped>
.product-outbound {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>