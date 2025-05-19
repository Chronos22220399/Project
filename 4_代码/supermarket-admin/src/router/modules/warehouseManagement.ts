export default {
    path: "/warehouseManagement",
    name: "WarehouseManagement",
    component: () => import("../../pages/warehouse/warehouseManagement.vue"),
    redirect: "/warehouseManagement/warehouseInfo",
    meta: { title: "仓库管理", icon: "warehouse" },
  children: [
    {
      path: "warehouseInfo",
      name: "WarehouseInfo",
      component: () => import("../../pages/warehouse/warehouseInfo.vue"),
      meta: { title: "仓库信息模块" },
    },
    {
      path: "productInbound",
      name: "ProductInbound",
      component: () => import("../../pages/warehouse/productInbound.vue"),
      meta: { title: "商品入库模块" },
    },
    {
      path: "productOutbound",
      name: "ProductOutbound",
      component: () => import("../../pages/warehouse/productOutbound.vue"),
      meta: { title: "商品出库模块" },
    },
    {
      path: "inventoryCheck",
      name: "InventoryCheck",
      component: () => import("../../pages/warehouse/inventoryCheck.vue"),
      meta: { title: "库存盘点模块" },
    },
    {
      path: "inventoryAlert",
      name: "InventoryAlert",
      component: () => import("../../pages/warehouse/inventoryAlert.vue"),
      meta: { title: "库存报警模块" },
    },
  ],
};
