<template>
    <el-card class="settings-card">
        <h3>系统管理功能</h3>
        <div class="grid-container">
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/userPermission')">
                用户权限管理
            </el-button>
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/systemLogs')">
                系统日志管理
            </el-button>
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/systemSettings')">
                系统设置
            </el-button>
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/systemUpdate')">
                系统更新与维护
            </el-button>
        </div>
    </el-card>
</template>

<style scoped>
.settings-card {
    background-image: url('../../components/layout/goods.jpg');
    padding: 30px;
    box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
    border-radius: 10px;
}

h3 {
    text-align: center;
    margin-bottom: 30px;
    font-weight: bold;
    font-size: 28px;
    color: #131212;
}

.grid-container {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    /* 两列 */
    grid-template-rows: repeat(2, auto);
    /* 两行 */
    grid-gap: 20px;
    justify-items: center;
}

/* 按钮样式 */
.setting-button {
    font-size: 20px;
    width: 280px;
    height: 280px;
    background-color: rgba(255, 255, 255, 0.5);
    color: #222;
    border: 2px solid rgba(255, 255, 255, 0.5);
    border-radius: 10px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.15);
    transition: all 0.3s ease-in-out;
    display: flex;
    justify-content: center;
    align-items: center;
}

/* 悬停效果 */
.setting-button:hover {
    opacity: 0.85;
    transform: scale(1.05);
    box-shadow: 0 8px 16px rgba(0, 0, 0, 0.2);
    border-color: #ff4081;
}

/* 焦点状态 */
.setting-button:focus {
    outline: none;
    box-shadow: 0 0 10px 2px rgba(255, 64, 129, 0.5);
}

/* 小屏幕适配：单列 */
@media (max-width: 768px) {
    .grid-container {
        grid-template-columns: 1fr;
    }

    .setting-button {
        width: 100%;
        height: 180px;
    }
}
</style>
