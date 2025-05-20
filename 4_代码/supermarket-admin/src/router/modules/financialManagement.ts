export default {
    path: "/financialManagement",
    name: "FinancialManagement",
    component: () => import("../../pages/financial/financialManagement.vue"),
    redirect: "/financial/cashierManagement", // 默认跳转到收银管理
    meta: { title: "财务管理", icon: "el-icon-credit-card" },
    children: [
      {
        path: "cashierManagement",
        name: "CashierManagement",
        component: () => import("../../pages/financial/cashierManagement.vue"),
        meta: { title: "收银管理" },
      },
      {
        path: "financialReport",
        name: "FinancialReport",
        component: () => import("../../pages/financial/financialReport.vue"),
        meta: { title: "财务报表生成" },
      },
      {
        path: "costAccounting",
        name: "CostAccounting",
        component: () => import("../../pages/financial/costAccounting.vue"),
        meta: { title: "成本核算" },
      },
      {
        path: "budgetManagement",
        name: "BudgetManagement",
        component: () => import("../../pages/financial/budgetManagement.vue"),
        meta: { title: "预算管理" },
      },
      {
        path: "taxManagement",
        name: "TaxManagement",
        component: () => import("../../pages/financial/taxManagement.vue"),
        meta: { title: "税务管理" },
      },
    ],
  };
  