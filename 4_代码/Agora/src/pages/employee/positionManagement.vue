<template>
    <el-card>
        <el-button type="primary" @click="addPosition">新增岗位</el-button>
        <el-table :data="positions">
            <el-table-column label="岗位名称" prop="name" />
            <el-table-column label="描述" prop="desc" />
            <el-table-column label="操作">
                <template #default="scope">
                    <el-button size="small" @click="edit(scope.row)">编辑</el-button>
                    <el-button size="small" type="danger">删除</el-button>
                </template>
            </el-table-column>
        </el-table>
    </el-card>
</template>

<script setup>
import { ref } from 'vue';
const positions = ref([{ name: '收银员', desc: '负责前台收银' }]);
const addPosition = () => { };
const edit = (row) => { };
</script>