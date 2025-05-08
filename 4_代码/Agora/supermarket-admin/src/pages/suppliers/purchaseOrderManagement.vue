<template>
    <div class="purchase-order-management">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="订单编号">
                        <el-input v-model="form.orderNumber" placeholder="请输入订单编号" />
                    </el-form-item>
                    <el-form-item label="供应商名称">
                        <el-input v-model="form.supplierName" placeholder="请输入供应商名称" />
                    </el-form-item>
                    <el-form-item label="商品名称">
                        <el-input v-model="form.productName" placeholder="请输入商品名称" />
                    </el-form-item>
                    <el-form-item label="数量">
                        <el-input v-model="form.quantity" type="number" placeholder="请输入采购数量" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitOrder">确认提交</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    orderNumber: '',
    supplierName: '',
    productName: '',
    quantity: '',
});

const submitOrder = () => {
    console.log('提交采购订单', form.value);
};
</script>

<style scoped>
.purchase-order-management {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>