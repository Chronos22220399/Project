<template>
    <el-card>
        <h3>财务报表</h3>
        <div ref="barChart" style="width: 100%; height: 300px; margin-bottom: 20px;"></div>
        <div ref="pieChart" style="width: 100%; height: 300px;"></div>
    </el-card>
</template>

<script setup lang="ts">
import * as echarts from 'echarts'
import { onMounted, ref } from 'vue'

const barChart = ref < HTMLElement | null > (null)
const pieChart = ref < HTMLElement | null > (null)

const barOption = {
    title: { text: '月度收入柱状图' },
    tooltip: {},
    xAxis: {
        type: 'category',
        data: ['1月', '2月', '3月', '4月', '5月', '6月']
    },
    yAxis: { type: 'value' },
    series: [{
        name: '收入',
        type: 'bar',
        data: [5000, 7000, 6000, 8000, 7500, 9000]
    }]
}

const pieOption = {
    title: { text: '支付方式占比', left: 'center' },
    tooltip: { trigger: 'item' },
    legend: { bottom: 10, left: 'center' },
    series: [
        {
            name: '支付方式',
            type: 'pie',
            radius: '50%',
            data: [
                { value: 1048, name: '现金' },
                { value: 735, name: '支付宝' },
                { value: 580, name: '微信' },
                { value: 484, name: '信用卡' }
            ],
            emphasis: {
                itemStyle: { shadowBlur: 10, shadowOffsetX: 0, shadowColor: 'rgba(0, 0, 0, 0.5)' }
            }
        }
    ]
}

onMounted(() => {
    if (barChart.value) {
        const bar = echarts.init(barChart.value)
        bar.setOption(barOption)
    }
    if (pieChart.value) {
        const pie = echarts.init(pieChart.value)
        pie.setOption(pieOption)
    }
})
</script>
