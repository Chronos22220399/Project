<!-- SalesReportView.vue -->
<template>
    <el-card>
        <el-row :gutter="20">
            <el-col :span="14">
                <el-table :data="paginatedData" border>
                    <el-table-column prop="report_month" label="统计月份" width="120" />
                    <el-table-column prop="total_orders" label="订单数量" />
                    <el-table-column prop="total_sales" label="销售总额（元）" />
                </el-table>
                <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
                    :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper"
                    style="margin-top: 10px" />
            </el-col>
            <el-col :span="10">
                <div ref="barChart" style="width: 100%; height: 300px" />
            </el-col>
        </el-row>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, watch } from 'vue'
import * as echarts from 'echarts'

interface SalesReport {
    report_month: string
    total_orders: number
    total_sales: number
}

const tableData = ref<SalesReport[]>(
    Array.from({ length: 12 }, (_, i) => ({
        report_month: `2024-${(i + 1).toString().padStart(2, '0')}`,
        total_orders: 100 + i * 10,
        total_sales: 100000 + i * 8000
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

const barChart = ref<HTMLDivElement | null>(null)

const renderChart = () => {
    if (!barChart.value) return

    const chart = echarts.init(barChart.value)
    const data = paginatedData.value

    chart.setOption({
        title: { text: '月销售总额柱状图', left: 'center' },
        tooltip: {},
        xAxis: {
            type: 'category',
            data: data.map(item => item.report_month)
        },
        yAxis: {
            type: 'value'
        },
        series: [
            {
                data: data.map(item => item.total_sales),
                type: 'bar',
                barWidth: '60%',
                itemStyle: { color: '#409EFF' }
            }
        ]
    })
}

onMounted(renderChart)
watch(paginatedData, renderChart)
</script>
