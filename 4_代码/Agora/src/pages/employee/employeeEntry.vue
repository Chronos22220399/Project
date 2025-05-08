<template>
    <el-card>
        <el-form :model="form" label-width="100px">
            <el-form-item label="姓名"><el-input v-model="form.name" /></el-form-item>
            <el-form-item label="性别">
                <el-radio-group v-model="form.gender">
                    <el-radio label="男" />
                    <el-radio label="女" />
                </el-radio-group>
            </el-form-item>
            <el-form-item label="岗位"><el-input v-model="form.position" /></el-form-item>
            <el-form-item label="联系方式"><el-input v-model="form.phone" /></el-form-item>
            <el-form-item>
                <el-button type="primary" @click="submit">提交</el-button>
            </el-form-item>
        </el-form>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';
const form = ref({ name: '', gender: '', position: '', phone: '' });
const submit = () => console.log('员工信息提交:', form.value);
</script>