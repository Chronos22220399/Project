<template>
    <div class="supplier-entry">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="供应商名称">
                        <el-input v-model="form.supplierName" placeholder="请输入供应商名称" />
                    </el-form-item>
                    <el-form-item label="联系人">
                        <el-input v-model="form.contactPerson" placeholder="请输入联系人" />
                    </el-form-item>
                    <el-form-item label="联系方式">
                        <el-input v-model="form.contactNumber" placeholder="请输入联系方式" />
                    </el-form-item>
                    <el-form-item label="地址">
                        <el-input v-model="form.address" placeholder="请输入供应商地址" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitSupplier">确认提交</el-button>
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
    contactPerson: '',
    contactNumber: '',
    address: '',
});

const submitSupplier = () => {
    console.log('提交供应商信息', form.value);
};
</script>

<style scoped>
.supplier-entry {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>