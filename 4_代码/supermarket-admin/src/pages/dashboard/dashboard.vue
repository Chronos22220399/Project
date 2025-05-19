<script setup lang="ts">
import { ref, onMounted, onUnmounted, watch } from "vue";
import * as echarts from "echarts";
import { ElCard, ElRadioGroup, ElRadioButton } from "element-plus";

// 图表容器
const lineChartRef = ref<HTMLElement>();
const barChartRef = ref<HTMLElement>();
const pieChartRef = ref<HTMLElement>();

// 当前视图类型（周 / 日）
const viewType = ref<'week' | 'day'>('week');

// 假数据
const dataMap = {
    week: {
        xAxis: ["周一", "周二", "周三", "周四", "周五", "周六", "周日"],
        line: [150, 230, 224, 218, 135, 147, 260],
        bar: [120, 200, 150, 80, 70, 110, 130],
        pie: [
            { value: 40, name: "食品" },
            { value: 20, name: "饮料" },
            { value: 15, name: "日用品" },
            { value: 25, name: "其他" }
        ]
    },
    day: {
        xAxis: ["0点", "4点", "8点", "12点", "16点", "20点"],
        line: [80, 110, 150, 230, 180, 200],
        bar: [70, 90, 130, 210, 160, 180],
        pie: [
            { value: 50, name: "食品" },
            { value: 25, name: "饮料" },
            { value: 10, name: "日用品" },
            { value: 15, name: "其他" }
        ]
    }
}

// 渲染图表
const renderCharts = () => {
    const chartData = dataMap[viewType.value];

    // 折线图
    if (lineChartRef.value) {
        const line = echarts.init(lineChartRef.value);
        line.setOption({
            title: { text: "销售趋势（折线图）" },
            xAxis: { type: "category", data: chartData.xAxis },
            yAxis: { type: "value" },
            series: [{ data: chartData.line, type: "line", smooth: true }]
        });
    }

    // 柱状图
    if (barChartRef.value) {
        const bar = echarts.init(barChartRef.value);
        bar.setOption({
            title: { text: "销售分布（柱状图）" },
            tooltip: {},
            xAxis: { data: chartData.xAxis },
            yAxis: {},
            series: [{ name: "销售额", type: "bar", data: chartData.bar }]
        });
    }

    // 饼状图
    if (pieChartRef.value) {
        const pie = echarts.init(pieChartRef.value);
        pie.setOption({
            title: { text: "商品类别占比（饼图）", left: "center" },
            tooltip: { trigger: "item" },
            legend: { bottom: "0%", left: "center" },
            series: [
                {
                    name: "类别占比",
                    type: "pie",
                    radius: "50%",
                    data: chartData.pie,
                    emphasis: {
                        itemStyle: {
                            shadowBlur: 10,
                            shadowOffsetX: 0,
                            shadowColor: "rgba(0, 0, 0, 0.5)"
                        }
                    }
                }
            ]
        });
    }
}

import image1 from '../../components/layout/goods03.jpeg';
import image2 from '../../components/layout/goods04.jpg';
import image3 from '../../components/layout/goods05.jpg';
import image4 from '../../components/layout/goods06.webp';

// 图片播放器相关
const images = [image1, image2, image3, image4];
const currentImageIndex = ref(0);
let imageTimer: number | undefined;

const showNextImage = () => {
    currentImageIndex.value = (currentImageIndex.value + 1) % images.length;
};

const showPrevImage = () => {
    currentImageIndex.value = (currentImageIndex.value - 1 + images.length) % images.length;
};

const startImageAutoPlay = () => {
    imageTimer = window.setInterval(showNextImage, 3000);
};

const stopImageAutoPlay = () => {
    if (imageTimer) {
        clearInterval(imageTimer);
        imageTimer = undefined;
    }
};

onMounted(() => {
    renderCharts();
    startImageAutoPlay();
});

onUnmounted(() => {
    stopImageAutoPlay();
});

watch(viewType, () => {
    renderCharts();
});
</script>

<template>
    <el-card>
        <template #header>
            <div style="display: flex; justify-content: space-between; align-items: center;">
                <span>销售数据总览</span>
                <el-radio-group v-model="viewType" size="small">
                    <el-radio-button label="week">周报</el-radio-button>
                    <el-radio-button label="day">日报</el-radio-button>
                </el-radio-group>
            </div>
        </template>

        <!-- 概览统计 -->
        <div style="display: flex; justify-content: space-around; margin-bottom: 20px;">
            <el-card style="width: 22%; text-align: center;">
                <div>今日总销售</div>
                <h2>¥12,500</h2>
            </el-card>
            <el-card style="width: 22%; text-align: center;">
                <div>订单数</div>
                <h2>235</h2>
            </el-card>
            <el-card style="width: 22%; text-align: center;">
                <div>退货数</div>
                <h2>13</h2>
            </el-card>
            <el-card style="width: 22%; text-align: center;">
                <div>新增客户</div>
                <h2>18</h2>
            </el-card>
        </div>

        <!-- 折线图 + 图片播放器 同行 -->
        <div style="display: flex; gap: 20px; margin-bottom: 20px;">
            <div ref="lineChartRef" style="width: 50%; height: 300px;"></div>

            <!-- 图片播放器 -->
            <div class="image-player" @mouseenter="stopImageAutoPlay" @mouseleave="startImageAutoPlay"
                style="width: 50%; height: 300px; position: relative; border-radius: 8px; overflow: hidden; box-shadow: 0 0 8px #aaa;">
                <img :src="images[currentImageIndex]" alt="轮播图" style="width: 100%; height: 100%; object-fit: cover;" />
                <button @click="showPrevImage" class="image-btn prev-btn" title="上一张">‹</button>
                <button @click="showNextImage" class="image-btn next-btn" title="下一张">›</button>
                <div class="dots">
                    <span v-for="(img, idx) in images" :key="idx" :class="{ active: idx === currentImageIndex }"
                        @click="currentImageIndex = idx"></span>
                </div>
            </div>
        </div>


        <!-- 柱状图 + 饼图 -->
        <div style="display: flex; gap: 20px;">
            <div ref="barChartRef" style="flex: 1; height: 300px;"></div>
            <div ref="pieChartRef" style="flex: 1; height: 300px;"></div>
        </div>
    </el-card>
</template>

<style scoped>
.el-card {
    margin-bottom: 20px;
}

/* 图片播放器按钮 */
.image-btn {
    position: absolute;
    top: 50%;
    transform: translateY(-50%);
    background: rgba(0, 0, 0, 0.3);
    border: none;
    color: white;
    font-size: 2rem;
    padding: 0 12px;
    cursor: pointer;
    user-select: none;
    border-radius: 4px;
    z-index: 10;
}

.prev-btn {
    left: 10px;
}

.next-btn {
    right: 10px;
}

/* 底部小圆点 */
.dots {
    position: absolute;
    bottom: 10px;
    width: 100%;
    text-align: center;
}

.dots span {
    display: inline-block;
    width: 10px;
    height: 10px;
    background: rgba(255, 255, 255, 0.6);
    margin: 0 6px;
    border-radius: 50%;
    cursor: pointer;
    transition: background 0.3s ease;
}

.dots span.active {
    background: rgba(255, 255, 255, 1);
}
</style>
