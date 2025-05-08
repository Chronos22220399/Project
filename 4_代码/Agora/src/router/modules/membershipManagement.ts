export default {
  path: "/membershipManagement",
  name: "MembershipManagement",
  component: () => import("../../pages/membership/membershipManagement.vue"),
  redirect: "/membershipManagement/memberEntry",
  meta: { title: "会员管理", icon: "users" },
  children: [
    {
      path: "memberEntry",
      name: "MemberEntry",
      component: () => import("../../pages/membership/memberEntry.vue"),
      meta: { title: "会员信息录入" },
    },
    {
      path: "levelManagement",
      name: "LevelManagement",
      component: () => import("../../pages/membership/levelManagement.vue"),
      meta: { title: "会员等级管理" },
    },
    {
      path: "pointPolicy",
      name: "PointPolicy",
      component: () => import("../../pages/membership/pointPolicy.vue"),
      meta: { title: "积分政策管理" },
    },
    {
      path: "consumptionRecord",
      name: "ConsumptionRecord",
      component: () => import("../../pages/membership/consumptionRecord.vue"),
      meta: { title: "会员消费记录管理" },
    },
    {
      path: "pointExchange",
      name: "PointExchange",
      component: () => import("../../pages/membership/pointExchange.vue"),
      meta: { title: "会员积分兑换管理" },
    },
  ],
};
