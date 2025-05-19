export default {
  path: "/employeeManagement",
  name: "EmployeeManagement",
  component: () => import("../../pages/employee/employeeManagement.vue"),
  redirect: "/employeeManagement/employeeEntry",
  meta: { title: "员工管理", icon: "user" },
  children: [
    {
      path: "employeeEntry",
      name: "EmployeeEntry",
      component: () => import("../../pages/employee/employeeEntry.vue"),
      meta: { title: "员工信息录入" },
    },
    {
      path: "positionManagement",
      name: "PositionManagement",
      component: () => import("../../pages/employee/positionManagement.vue"),
      meta: { title: "岗位管理" },
    },
    {
      path: "shiftManagement",
      name: "ShiftManagement",
      component: () => import("../../pages/employee/shiftManagement.vue"),
      meta: { title: "员工排班管理" },
    },
    {
      path: "attendanceManagement",
      name: "AttendanceManagement",
      component: () => import("../../pages/employee/attendanceManagement.vue"),
      meta: { title: "考勤管理" },
    },
    {
      path: "salaryManagement",
      name: "SalaryManagement",
      component: () => import("../../pages/employee/salaryManagement.vue"),
      meta: { title: "工资管理" },
    },
  ],
};