<template>
    <el-card>
        <el-form :model="policy" label-width="120px">
            <el-form-item label="消费积分规则">
                <el-input v-model="policy.rule" placeholder="如：每消费10元积1分" />
            </el-form-item>
            <el-form-item label="积分有效期">
                <el-input v-model="policy.expiry" placeholder="如：365天" />
            </el-form-item>
            <el-form-item>
                <el-button type="primary" @click="savePolicy">保存</el-button>
            </el-form-item>
        </el-form>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';

const policy = ref({
    rule: '',
    expiry: ''
});

const savePolicy = () => {
    console.log('保存积分政策：', policy.value);
};
</script>