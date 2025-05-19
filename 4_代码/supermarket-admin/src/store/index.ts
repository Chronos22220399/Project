import { defineStore } from "pinia";

export const useUserStore = defineStore("us er", {
state: () => ({ username: "Admin" }),
actions: {
setUser(name: string) {
this.username = name;
},
},
});
