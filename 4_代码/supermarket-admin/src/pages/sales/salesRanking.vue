<!-- SalesRankingView.vue -->
<template>
    <el-card>
        <el-row :gutter="20">
            <el-col :span="14">
                <el-table :data="paginatedData" border>
                    <el-table-column type="index" label="排名" width="80" />
                    <el-table-column prop="product_name" label="商品名称" />
                    <el-table-column prop="sales_volume" label="销售量" />
                    <el-table-column prop="sales_amount" label="销售金额（元）" />
                </el-table>
                <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
                    :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
                    style="margin-top: 10px" />
            </el-col>
            <el-col :span="10">
                <div ref="pieChart" style="width: 100%; height: 300px" />
            </el-col>
        </el-row>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, watch } from 'vue'
import * as echarts from 'echarts'

interface SalesRanking {
    product_name: string
    sales_volume: number
    sales_amount: number
}

const tableData = ref<SalesRanking[]>(
    Array.from({ length: 10 }, (_, i) => ({
        product_name: `商品-${i + 1}`,
        sales_volume: 100 - i * 2,
        sales_amount: 10000 - i * 300
    }))
)

const currentPage = ref(1)
const pageSize = ref(5)

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const handlePageChange = (page: number) => {
    currentPage.value = page
}

const pieChart = ref<HTMLDivElement | null>(null)

const renderChart = () => {
    if (!pieChart.value) return

    const chart = echarts.init(pieChart.value)

    chart.setOption({
        title: { text: '商品销售占比', left: 'center' },
        tooltip: { trigger: 'item' },
        series: [
            {
                name: '销售金额',
                type: 'pie',
                radius: '60%',
                data: paginatedData.value.map(item => ({
                    name: item.product_name,
                    value: item.sales_amount
                })),
                emphasis: {
                    itemStyle: {
                        shadowBlur: 10,
                        shadowOffsetX: 0,
                        shadowColor: 'rgba(0, 0, 0, 0.5)'
                    }
                }
            }
        ]
    })
}

onMounted(renderChart)
watch(paginatedData, renderChart)
</script>
