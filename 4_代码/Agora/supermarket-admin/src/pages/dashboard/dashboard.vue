<script setup lang="ts">
import { ref, onMounted } from "vue";
import * as echarts from "echarts";

const chartRef = ref();

onMounted(() => {
    const chart = echarts.init(chartRef.value);
    chart.setOption({
        title: { text: "销售趋势" },
        xAxis: { type: "category", data: ["周一", "周二", "周三", "周四", "周五", "周六", "周日"] },
        yAxis: { type: "value" },
        series: [{ data: [150, 230, 224, 218, 135, 147, 260], type: "line" }],
    });
});
</script>

<template>
    <el-card>
        <div ref="chartRef" style="width: 100%; height: 300px;"></div>
    </el-card>
</template>
