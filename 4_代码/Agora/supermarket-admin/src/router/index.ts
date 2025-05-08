import { createRouter, createWebHistory } from "vue-router";
import dashboard from "./modules/dashboard";
import membershipManagement from "./modules/membershipManagement.ts";
import warehouseManagement from "./modules/warehouseManagement.ts";
import employeeManagement from "./modules/employeeManagement.ts";
import goodsManagement from "./modules/goodsManagement.ts";
import financialManagement from "./modules/financialManagement.ts";
import systemManagement from "./modules/systemManagement.ts";
import salesManagement from "./modules/salesManagement.ts";
import supplierManagement from "./modules/supplierManagement.ts";
import Layout from "../layout/Layout.vue";
import settings from "./modules/settings.ts";
//懒加载登录界面
const login = { name: "Login", path: "/login", component: () => import("../pages/login/Login.vue") };

const routes = [
  {
    path: "/login",
    component: login.component,
    name: "Login",
    meta: { requireAuth: false },
  },
  {
    path: "/",
    component: Layout,
    redirect: "/login",
    children: 
    [
      dashboard, 
      membershipManagement, 
      warehouseManagement, 
      goodsManagement, 
      employeeManagement,
      financialManagement,
      systemManagement,
      settings, 
      supplierManagement,
      salesManagement
],
  },
  
];

const router = createRouter({
  history: createWebHistory(),
  routes,
});

//添加全局路由守卫，设置未登录时跳转至登录界面
router.beforeEach((to, _from, next) => {
  const isAuthenticated = !!localStorage.getItem("token");//判断是否登录
  if (to.meta.requireAuth !== false && !isAuthenticated) {
    next("/login")
  }else{
    next()
  }
});

export default router;
