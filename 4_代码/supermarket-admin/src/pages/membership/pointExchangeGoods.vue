<template>
  <el-card>
    <div class="toolbar">
      <el-button type="primary" @click="openDialog()">添加物品</el-button>
    </div>
    <el-table :data="paginatedData" border style="width: 100%">
      <el-table-column prop="id" label="物品ID" width="100" />
      <el-table-column prop="name" label="物品名称" />
      <el-table-column prop="pointsRequired" label="所需积分" />
      <el-table-column prop="startTime" label="开始时间" />
      <el-table-column prop="endTime" label="结束时间" />
      <el-table-column label="操作" width="180">
        <template #default="scope">
          <el-button size="small" @click="openDialog(scope.row)">编辑</el-button>
          <el-button size="small" type="danger" @click="handleDelete(scope.row.id)">删除</el-button>
        </template>
      </el-table-column>
    </el-table>
    <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
      :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"></el-pagination>

    <el-dialog :title="dialogTitle" v-model="dialogVisible">
      <el-form :model="form">
        <el-form-item label="物品名称"><el-input v-model="form.name" /></el-form-item>
        <el-form-item label="所需积分"><el-input v-model="form.pointsRequired" /></el-form-item>
        <el-form-item label="开始时间"><el-date-picker v-model="form.startTime" type="date" /></el-form-item>
        <el-form-item label="结束时间"><el-date-picker v-model="form.endTime" type="date" /></el-form-item>
      </el-form>
      <template #footer>
        <el-button @click="dialogVisible = false">取消</el-button>
        <el-button type="primary" @click="handleSave">保存</el-button>
      </template>
    </el-dialog>
  </el-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'

interface RedeemItem {
  id: number
  name: string
  pointsRequired: number
  startTime: string
  endTime: string
}

const generateFakeItems = (): RedeemItem[] => {
  return Array.from({ length: 20 }, (_, i) => ({
    id: i + 1,
    name: `礼品${i + 1}`,
    pointsRequired: (i + 1) * 10,
    startTime: '2025-01-01',
    endTime: '2025-12-31'
  }))
}

const tableData = ref<RedeemItem[]>(generateFakeItems())
const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const dialogTitle = ref('添加物品')
const form = ref<Partial<RedeemItem>>({})

const paginatedData = computed(() => {
  const start = (currentPage.value - 1) * pageSize.value
  return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: RedeemItem) => {
  dialogTitle.value = row ? '编辑物品' : '添加物品'
  form.value = row ? { ...row } : {}
  dialogVisible.value = true
}

const handleSave = () => {
  if (form.value.id) {
    const index = tableData.value.findIndex(item => item.id === form.value.id)
    if (index !== -1) {
      tableData.value[index] = { ...(form.value as RedeemItem) }
    }
  } else {
    const newId = Date.now()
    tableData.value.push({ ...(form.value as RedeemItem), id: newId })
  }
  dialogVisible.value = false
}

const handleDelete = (id: number) => {
  tableData.value = tableData.value.filter(item => item.id !== id)
}

const handlePageChange = (page: number) => {
  currentPage.value = page
}
</script>

<style scoped>
.toolbar {
  margin-bottom: 12px;
}
</style>
