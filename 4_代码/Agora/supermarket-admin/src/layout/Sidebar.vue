<script setup lang="ts">
import { useRouter, useRoute } from 'vue-router';
import { computed, ref, watch } from 'vue';
import SettingsButton from './SettingsButton.vue'; // 引入设置按钮组件

// Vue Router 实例
const router = useRouter();
const route = useRoute();

// 菜单数据
const menuItems = [
    { name: "销售记录", path: "/dashboard", icon: "Odometer" },
    {
        name: "商品管理", path: "/productsManagement",
        children: [
            { name: "商品信息录入", path: "productEntry" },
            { name: "商品分类管理", path: "categoryManagement" },
            { name: "商品库存管理", path: "inventoryManagement" },
            { name: "商品价格管理", path: "pricingManagement" },
            { name: "促销活动管理", path: "promotionManagement" },
        ],
    },
    {
        name: "仓库管理", path: "/warehouseManagement",
        children: [
            { name: "仓库信息管理", path: "warehouseInfo" },
            { name: "商品入库管理", path: "productInbound" },
            { name: "商品出库管理", path: "productOutbound" },
            { name: "库存盘点管理", path: "inventoryCheck" },
            { name: "库存报警管理", path: "inventoryAlert" },
        ]
    },
    {
        name: "财务管理",
        path: "/financialManagement",
        children: [
            { name: "收银管理", path: "cashierManagement" },
            { name: "财务报表生成", path: "financialReport" },
            { name: "成本核算", path: "costAccounting" },
            { name: "预算管理", path: "budgetManagement" },
            { name: "税务管理", path: "taxManagement" },
        ]
    },
    {
        name: "员工管理",
        path: "/employeeManagement",
        children: [
            { name: "员工信息录入", path: "employeeEntry" },
            { name: "岗位管理", path: "positionManagement" },
            { name: "员工排班管理", path: "shiftManagement" },
            { name: "考勤管理", path: "attendanceManagement" },
            { name: "工资管理", path: "salaryManagement" },
        ],
    },
    {
        name: "会员管理",
        path: "/membershipManagement",
        children: [
            { name: "会员信息录入", path: "memberEntry" },
            { name: "会员等级管理", path: "levelManagement" },
            { name: "积分政策管理", path: "pointPolicy" },
            { name: "会员消费记录管理", path: "consumptionRecord" },
            { name: "会员积分兑换管理", path: "pointExchange" },
        ],
    },
    {
        name: "销售管理",
        path: "/salesManagement",
        children: [
            { name: "销售订单录入", path: "orderEntry" },
            { name: "销售退货管理", path: "returnManagement" },
            { name: "销售统计报表", path: "salesReport" },
            { name: "商品销售排行榜", path: "salesRanking" },
        ],
    },
    {
        name: "供应商管理",
        path: "/supplierManagement",
        children: [
            { name: "供应商信息录入", path: "supplierEntry" },
            { name: "供应商合同管理", path: "contractManagement" },
            { name: "供应商评价管理", path: "supplierEvaluation" },
            { name: "采购订单管理", path: "purchaseOrderManagement" },
        ],
    },
    // {
    //     name: "系统管理",
    //     path: "/systemManagement",
    //     children: [
    //         { name: "用户权限管理", path: "userPermission" },
    //         { name: "系统日志管理", path: "systemLogs" },
    //         { name: "数据备份与恢复", path: "dataBackup" },
    //         { name: "系统设置", path: "systemSettings" },
    //         { name: "系统更新与维护", path: "systemUpdate" },
    //     ],
    // },
];

// 当前激活菜单项
const activeMenu = ref(route.path);
watch(
    () => route.path,
    (newPath) => {
        activeMenu.value = newPath;
    }
);

// 当前展开的模块（如 "productsManagement"）
const activeModule = ref<string | null>(null);

// 菜单跳转
const navigate = (path: string, parentPath?: string) => {
    if (path === '/settings') {
        // 设置特殊处理，不改变模块状态
        router.push(path);
        return;
    }

    const fullPath = parentPath ? `${parentPath}/${path}` : path;
    router.push(fullPath);

    const parentPathMatch = fullPath.split('/')[1];
    activeModule.value = parentPathMatch;
};

// 返回主菜单（显示所有模块）
const returnToMainMenu = () => {
    activeModule.value = null;
    router.push('/dashboard');
};

// 根据当前模块计算需要显示的菜单项
const visibleMenuItems = computed(() => {
    if (activeModule.value) {
        return menuItems.filter(item => item.path === `/${activeModule.value}`);
    }
    return menuItems;
});
</script>

<template>
    <el-menu :default-active="activeMenu" class="el-menu-vertical" router>
        <!-- 动态菜单 -->
        <template v-for="item in visibleMenuItems" :key="item.path">
            <el-menu-item v-if="!item.children" :index="item.path" @click="navigate(item.path)">
                <el-icon>
                    <component :is="item.icon" />
                </el-icon>
                <span>{{ item.name }}</span>
            </el-menu-item>

            <el-sub-menu v-else :index="item.path">
                <template #title>
                    <el-icon>
                        <component :is="item.icon" />
                    </el-icon>
                    <span>{{ item.name }}</span>
                </template>
                <el-menu-item v-for="child in item.children" :key="child.path" :index="`${item.path}/${child.path}`"
                    @click="navigate(child.path, item.path)">
                    {{ child.name }}
                </el-menu-item>
            </el-sub-menu>
        </template>

        <!-- 返回主菜单按钮 -->
        <div v-if="activeModule" class="return-button-wrapper">
            <el-button type="primary" size="small" @click="returnToMainMenu" class="return-button">
                返回菜单
            </el-button>
        </div>

        <!-- 设置按钮 -->
        <div class="settings-module">
            <SettingsButton />
        </div>
    </el-menu>
</template>

<style scoped>
.el-menu {
    height: 100vh;
    position: relative;
    padding-bottom: 90px;
    /* 留出底部按钮区域空间 */
}

.return-button-wrapper {
    position: absolute;
    bottom: 80px;
    /* 调整距离底部的距离 */
    width: 100%;
    display: flex;
    justify-content: center;
    padding: 0px;
}

.return-button {
    width: 80px;
    height: 40px;
    border-radius: 12px;
    font-size: 16px;
    font-weight: bold;
    color: rgb(9, 9, 9);
    background: rgba(255, 255, 255, 0.15);
    /* 半透明白色背景 */
    backdrop-filter: blur(6px);
    /* 背景模糊 */
    display: flex;
    align-items: center;
    justify-content: center;
    text-align: center;
    cursor: pointer;
    box-shadow: 0 4px 10px rgba(0, 0, 0, 0.15);
    transition: all 0.3s ease;
    border: none;
}

.return-button:hover {
    background: rgba(176, 26, 26, 0.25);
    /* 悬浮更亮 */
    transform: scale(1.05);
}

.settings-module {
    position: absolute;
    bottom: 0;
    width: 100%;
    display: flex;
    justify-content: center;
}

.settings-item {
    display: flex;
    align-items: center;
    justify-content: flex-start;
    padding: 0px;
}

.settings-icon {
    width: 20px;
    height: 20px;
}
</style>
