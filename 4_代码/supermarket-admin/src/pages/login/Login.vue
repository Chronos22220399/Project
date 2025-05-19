<template>
    <div class="login-container">
        <el-card class="login-card">
            <h2 class="title">超市管理系统</h2>
            <el-form :model="loginForm" :rules="rules" ref="loginFormRef" class="login-form">
                <el-form-item prop="username">
                    <el-input v-model="loginForm.username" placeholder="请输入账号">
                        <template #prefix>
                            <el-icon>
                                <User />
                            </el-icon>
                        </template>
                    </el-input>
                </el-form-item>
                <el-form-item prop="password">
                    <el-input v-model="loginForm.password" type="password" placeholder="请输入密码">
                        <template #prefix>
                            <el-icon>
                                <Lock />
                            </el-icon>
                        </template>
                    </el-input>
                </el-form-item>
                <el-form-item>
                    <el-checkbox v-model="loginForm.rememberMe">记住我</el-checkbox>
                </el-form-item>
                <el-form-item>
                    <el-button type="primary" @click="handleLogin" class="login-btn">登录</el-button>
                </el-form-item>
            </el-form>
        </el-card>
    </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from "vue";
import { useRouter } from "vue-router";
import { ElMessage } from "element-plus";
import { User, Lock } from "@element-plus/icons-vue";

const router = useRouter();

const loginForm = ref({
    username: "",
    password: "",
    rememberMe: false,
});

const loginFormRef = ref();

//读取本地存储的账号信息
onMounted(() => {
    const savedUser = localStorage.getItem("savedUser");
    if (savedUser) {
        const { username, password, rememberMe } = JSON.parse(savedUser);
        loginForm.value = { username, password, rememberMe };
    }
});

//表单验证规则
const rules = {
    username: [{ required: true, message: "请输入账号", trigger: "blur" }],
    password: [{ required: true, message: "请输入密码", trigger: "blur" }],
};

const handleLogin = () => {
    (loginFormRef.value as any).validate((valid: boolean) => {
        if (valid) {
            //模拟登录
            if (loginForm.value.username === "admin" && loginForm.value.password === "123456") {
                ElMessage.success("登录成功！");

                //存储 token
                localStorage.setItem("token", "your-secure-token");

                //记住密码
                if (loginForm.value.rememberMe) {
                    localStorage.setItem("savedUser", JSON.stringify(loginForm.value));
                } else {
                    localStorage.removeItem("savedUser");
                }

                //跳转
                router.push("/dashboard");
            } else {
                ElMessage.error("账号或密码错误！");
            }
        } else {
            ElMessage.error("请填写完整信息！");
        }
    });
};
</script>

<style scoped>
.login-container {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
    background-color: #f5f5f5;
}

.login-card {
    width: 350px;
    padding: 20px;
    text-align: center;
    background: #fff;
    box-shadow: 0px 4px 12px rgba(0, 0, 0, 0.1);
    border-radius: 10px;
}

.title {
    font-size: 22px;
    font-weight: bold;
    margin-bottom: 20px;
}

.login-form {
    width: 100%;
}

.login-btn {
    width: 100%;
}
</style>
