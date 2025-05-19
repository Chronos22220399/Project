export default {
    path: "/supplierManagement",
    name: "SupplierManagement",
    component: () => import("../../pages/suppliers/supplierManagement.vue"),
    redirect: "/supplierManagement/supplierEntry",
    meta: { title: "供应商管理", icon: "truck" },
    children: [
      {
        path: "supplierEntry",
        name: "SupplierEntry",
        component: () => import("../../pages/suppliers/supplierEntry.vue"),
        meta: { title: "供应商信息录入" },
      },
      {
        path: "contractManagement",
        name: "ContractManagement",
        component: () => import("../../pages/suppliers/contractManagement.vue"),
        meta: { title: "供应商合同管理" },
      },
      {
        path: "supplierEvaluation",
        name: "SupplierEvaluation",
        component: () => import("../../pages/suppliers/supplierEvaluation.vue"),
        meta: { title: "供应商评价管理" },
      },
      {
        path: "purchaseOrderManagement",
        name: "PurchaseOrderManagement",
        component: () => import("../../pages/suppliers/purchaseOrderManagement.vue"),
        meta: { title: "采购订单管理" },
      },
    ],
  };
  