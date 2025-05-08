<template>
    <div class="return-management">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="退货单编号">
                        <el-input v-model="form.returnOrderNumber" placeholder="请输入退货单编号" />
                    </el-form-item>
                    <el-form-item label="商品名称">
                        <el-input v-model="form.productName" placeholder="请输入商品名称" />
                    </el-form-item>
                    <el-form-item label="数量">
                        <el-input v-model="form.quantity" type="number" placeholder="请输入退货数量" />
                    </el-form-item>
                    <el-form-item label="客户">
                        <el-input v-model="form.customerName" placeholder="请输入客户名称" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitReturn">确认退货</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    returnOrderNumber: '',
    productName: '',
    quantity: '',
    customerName: '',
});

const submitReturn = () => {
    console.log('提交退货', form.value);
};
</script>

<style scoped>
.return-management {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>