export default {
    path: "/salesManagement",
    name: "SalesManagement",
    component: () => import("../../pages/sales/salesManagement.vue"),
    redirect: "/salesManagement/orderEntry",
    meta: { title: "销售管理", icon: "shopping-cart" },
    children: [
      {
        path: "orderEntry",
        name: "OrderEntry",
        component: () => import("../../pages/sales/orderEntry.vue"),
        meta: { title: "销售订单录入" },
      },
      {
        path: "returnManagement",
        name: "ReturnManagement",
        component: () => import("../../pages/sales/returnManagement.vue"),
        meta: { title: "销售退货管理" },
      },
      {
        path: "salesReport",
        name: "SalesReport",
        component: () => import("../../pages/sales/salesReport.vue"),
        meta: { title: "销售统计报表" },
      },
      {
        path: "salesRanking",
        name: "SalesRanking",
        component: () => import("../../pages/sales/salesRanking.vue"),
        meta: { title: "商品销售排行榜" },
      },
    ],
  };
  