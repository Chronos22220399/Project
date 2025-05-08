<template>
    <div class="page-container">
        <h2>商品价格管理</h2>

        <!-- 促销规则管理 -->
        <div class="promotion-section">
            <el-input v-model="newPromotion.name" placeholder="输入促销活动名称" class="input-box" />
            <el-input v-model="newPromotion.discount" type="number" placeholder="输入促销折扣 (%)" class="input-box" />
            <el-button type="primary" @click="addPromotion">添加折扣促销规则</el-button>

            <!-- 满减规则 -->
            <el-input v-model="newFullReduction.condition" type="number" placeholder="输入满减条件 (如满100)"
                class="input-box" />
            <el-input v-model="newFullReduction.discount" type="number" placeholder="输入满减金额 (如减20)" class="input-box" />
            <el-button type="primary" @click="addFullReduction">添加满减规则</el-button>

            <el-table :data="promotions" border style="width: 100%">
                <el-table-column prop="name" label="促销规则"></el-table-column>
                <el-table-column prop="discount" label="折扣（%）"></el-table-column>
                <el-table-column label="操作">
                    <template #default="{ row }">
                        <el-button type="danger" @click="removePromotion(row)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <el-table :data="fullReductions" border style="width: 100%">
                <el-table-column prop="condition" label="满减条件"></el-table-column>
                <el-table-column prop="discount" label="满减金额"></el-table-column>
                <el-table-column label="操作">
                    <template #default="{ row }">
                        <el-button type="danger" @click="removeFullReduction(row)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>
        </div>

        <!-- 商品价格表 -->
        <el-table :data="products" border style="width: 100%">
            <el-table-column prop="name" label="商品名称"></el-table-column>
            <el-table-column label="成本价">
                <template #default="{ row }">
                    <el-input v-model.number="row.cost" placeholder="输入成本价" size="small" class="cost-input" />
                </template>
            </el-table-column>
            <el-table-column label="促销折扣（%）">
                <template #default="{ row }">
                    <el-select v-model="row.promotion" multiple placeholder="选择促销" size="small"
                        class="promotion-select">
                        <el-option v-for="promotion in promotions" :key="promotion.name" :label="promotion.name"
                            :value="promotion.discount"></el-option>
                    </el-select>
                </template>
            </el-table-column>

            <el-table-column label="满减规则">
                <template #default="{ row }">
                    <el-select v-model="row.fullReduction" multiple placeholder="选择满减规则" size="small"
                        class="full-reduction-select">
                        <el-option v-for="fullReduction in fullReductions" :key="fullReduction.condition"
                            :label="`满${fullReduction.condition}减${fullReduction.discount}`" :value="fullReduction" />
                    </el-select>
                </template>
            </el-table-column>

            <el-table-column label="最终价格">
                <template #default="{ row }">
                    <el-input v-model="row.price" placeholder="最终价格" size="small" disabled class="price-input" />
                </template>
            </el-table-column>
            <el-table-column label="操作">
                <template #default="{ row }">
                    <el-button type="primary" @click="calculatePrice(row)">计算价格</el-button>
                </template>
            </el-table-column>
        </el-table>
    </div>
</template>

<script setup lang="ts">

import { ref } from "vue";
import { ElMessage } from "element-plus";

// 促销规则
const promotions = ref([{ name: "双十一特惠", discount: 20 }, { name: "满减活动", discount: 10 }]);
const newPromotion = ref({
    name: "",
    discount: 0
});

// 满减规则
const fullReductions = ref([
    { condition: 100, discount: 20 },
    { condition: 200, discount: 50 },
    { condition: 50, discount: 10 } // 添加一个小额的满减规则
]);
const newFullReduction = ref({
    condition: 0,
    discount: 0
});

// 商品列表
const products = ref([
    { name: "牛奶", cost: 5, promotion: [], fullReduction: [], price: 5 },
    { name: "面包", cost: 10, promotion: [], fullReduction: [], price: 10 },
    { name: "水果", cost: 15, promotion: [], fullReduction: [], price: 15 },
]);

// 计算单个商品的最终价格
const calculatePrice = (row: any) => {
    let finalPrice = row.cost;  // 初始化最终价格为成本价

    // 遍历促销活动，计算每个折扣
    row.promotion.forEach((discount: number) => {
        finalPrice *= (1 - discount / 100);  // 每个折扣依次应用
    });

    // 计算满减规则
    row.fullReduction.forEach((rule: any) => {
        finalPrice = finalPrice >= rule.condition ? finalPrice - rule.discount : finalPrice;
    });

    row.price = finalPrice;
    ElMessage.success(`价格计算完成: ${row.name} 价格为 ¥${row.price.toFixed(2)}`);
};

// 添加折扣促销规则
const addPromotion = () => {
    if (newPromotion.value.name.trim() && newPromotion.value.discount > 0) {
        promotions.value.push({
            name: newPromotion.value.name,
            discount: newPromotion.value.discount
        });
        ElMessage.success("折扣促销规则添加成功");
        newPromotion.value.name = "";
        newPromotion.value.discount = 0;
    } else {
        ElMessage.error("请输入促销活动名称和折扣");
    }
};

// 删除折扣促销规则
const removePromotion = (promotion: any) => {
    promotions.value = promotions.value.filter((p) => p.name !== promotion.name);
    ElMessage.success("折扣促销规则删除成功");
};

// 添加满减规则
const addFullReduction = () => {
    if (newFullReduction.value.condition > 0 && newFullReduction.value.discount > 0) {
        fullReductions.value.push({
            condition: newFullReduction.value.condition,
            discount: newFullReduction.value.discount
        });
        ElMessage.success("满减规则添加成功");
        newFullReduction.value.condition = 0;
        newFullReduction.value.discount = 0;
    } else {
        ElMessage.error("请输入满减条件和金额");
    }
};

// 删除满减规则
const removeFullReduction = (fullReduction: any) => {
    fullReductions.value = fullReductions.value.filter((fr) => fr.condition !== fullReduction.condition);
    ElMessage.success("满减规则删除成功");
};
</script>

<style scoped>
.page-container {
    padding: 20px;
    background-color: #f5f5f5;
    /* 背景色 */
    border-radius: 8px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    /* 添加阴影 */
}

h2 {
    font-size: 24px;
    font-weight: 600;
    margin-bottom: 20px;
    color: #333;
    /* 标题颜色 */
}

.promotion-section {
    background-color: #ffffff;
    /* 背景色 */
    padding: 15px;
    border-radius: 8px;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    /* 添加阴影 */
    margin-bottom: 20px;
}

.input-box {
    margin-right: 10px;
    width: 220px;
    /* 固定宽度 */
    padding: 8px;
    border-radius: 4px;
    border: 1px solid #dcdfe6;
    font-size: 14px;
}

.el-button {
    margin-left: 10px;
}

.el-table {
    background-color: #ffffff;
    border-radius: 8px;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    /* 添加阴影 */
}

.el-table-column {
    text-align: center;
}

.el-table th {
    background-color: #f4f4f4;
    font-size: 14px;
    font-weight: 500;
}

.el-button.primary {
    background-color: #409EFF;
    border-color: #409EFF;
}

.el-button.primary:hover {
    background-color: #66b1ff;
    border-color: #66b1ff;
}

.el-button.danger {
    background-color: #f56c6c;
    border-color: #f56c6c;
}

.el-button.danger:hover {
    background-color: #f78989;
    border-color: #f78989;
}

.el-button.warning {
    background-color: #e6a23c;
    border-color: #e6a23c;
}

.el-button.warning:hover {
    background-color: #f7bc77;
    border-color: #f7bc77;
}

.el-button.success {
    background-color: #67c23a;
    border-color: #67c23a;
}

.el-button.success:hover {
    background-color: #85d97e;
    border-color: #85d97e;
}

.promotion-select {
    width: 150px;
    margin: 5px;
}

.price-input {
    width: 100px;
    padding: 5px;
    text-align: center;
}
</style>