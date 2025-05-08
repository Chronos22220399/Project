<template>
    <div class="system-settings">
        <el-card>
            <div class="form-area">
                <el-form :model="form" label-width="120px">
                    <el-form-item label="系统语言">
                        <el-select v-model="form.language" placeholder="请选择系统语言">
                            <el-option label="中文" value="zh" />
                            <el-option label="英文" value="en" />
                        </el-select>
                    </el-form-item>
                    <el-form-item label="时间格式">
                        <el-select v-model="form.timeFormat" placeholder="请选择时间格式">
                            <el-option label="12小时制" value="12hr" />
                            <el-option label="24小时制" value="24hr" />
                        </el-select>
                    </el-form-item>
                    <el-form-item label="数据存储路径">
                        <el-input v-model="form.storagePath" placeholder="请输入数据存储路径" />
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="submitSettings">保存设置</el-button>
                    </el-form-item>
                </el-form>
            </div>
        </el-card>
    </div>
</template>

<script setup>
import { ref } from 'vue';

const form = ref({
    language: 'zh',
    timeFormat: '24hr',
    storagePath: '/data/storage',
});

const submitSettings = () => {
    console.log('保存系统设置', form.value);
};
</script>

<style scoped>
.system-settings {
    padding: 20px;
}

.form-area {
    max-width: 600px;
    margin: 0 auto;
}
</style>