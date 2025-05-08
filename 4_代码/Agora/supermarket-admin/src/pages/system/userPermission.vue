<template>
    <div class="user-permissions">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="用户名称">
                        <el-input v-model="form.userName" placeholder="请输入用户名称" />
                    </el-form-item>
                    <el-form-item label="权限级别">
                        <el-select v-model="form.role" placeholder="请选择权限级别">
                            <el-option label="管理员" value="admin" />
                            <el-option label="普通用户" value="user" />
                        </el-select>
                    </el-form-item>
                    <el-form-item label="操作权限">
                        <el-checkbox-group v-model="form.permissions">
                            <el-checkbox label="查看" value="view" />
                            <el-checkbox label="编辑" value="edit" />
                            <el-checkbox label="删除" value="delete" />
                        </el-checkbox-group>
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitPermissions">确认提交</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    userName: '',
    role: '',
    permissions: [],
});

const submitPermissions = () => {
    console.log('提交用户权限', form.value);
};
</script>

<style scoped>
.user-permissions {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>