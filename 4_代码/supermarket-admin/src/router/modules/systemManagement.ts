export default {
    path: "/systemManagement",
    name: "SystemManagement",
    component: () => import("../../pages/system/systemManagement.vue"),
    redirect: "/systemManagement/userPermission",
    meta: { title: "系统管理", icon: "settings" },
    children: [
      {
        path: "userPermission",
        name: "UserPermission",
        component: () => import("../../pages/system/userPermission.vue"),
        meta: { title: "用户权限管理" },
      },
      {
        path: "systemLogs",
        name: "SystemLogs",
        component: () => import("../../pages/system/systemLogs.vue"),
        meta: { title: "系统日志管理" },
      },
      {
        path: "dataBackup",
        name: "DataBackup",
        component: () => import("../../pages/system/dataBackup.vue"),
        meta: { title: "数据备份与恢复" },
      },
      {
        path: "systemSettings",
        name: "SystemSettings",
        component: () => import("../../pages/system/systemSettings.vue"),
        meta: { title: "系统设置" },
      },
      {
        path: "systemUpdate",
        name: "SystemUpdate",
        component: () => import("../../pages/system/systemUpdate.vue"),
        meta: { title: "系统更新与维护" },
      },
    ],
  };