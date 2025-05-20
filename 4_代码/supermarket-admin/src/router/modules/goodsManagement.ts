export default {
    path: "/productsManagement",
    name: "ProductsManagement",
    component: () => import("../../pages/goods/goodsManagement.vue"),
    redirect: "/productsManagement/productEntry",
    meta: { title: "商品管理", icon: "shopping-cart" },
  children: [
    {
      path: "productEntry",
      name: "ProductEntry",
      component: () => import("../../pages/goods/goodsEntry.vue"),
      meta: { title: "商品信息录入" },
    },
    {
      path: "categoryManagement",
      name: "CategoryManagement",
      component: () => import("../../pages/goods/categoryManagement.vue"),
      meta: { title: "商品分类管理" },
    },
    {
      path: "inventoryManagement",
      name: "InventoryManagement",
      component: () => import("../../pages/goods/inventoryManagement.vue"),
      meta: { title: "商品库存管理" },
    },
    {
      path: "pricingManagement",
      name: "PricingManagement",
      component: () => import("../../pages/goods/pricingManagement.vue"),
      meta: { title: "商品价格管理" },
    },
    {
      path: "promotionManagement",
      name: "PromotionManagement",
      component: () => import("../../pages/goods/promotionManagement.vue"),
      meta: { title: "促销活动管理" },
    },
  ],
  
  };
  