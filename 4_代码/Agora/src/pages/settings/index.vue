<template>
    <el-card class="settings-card">
        <h3>系统管理功能</h3>
        <el-div class="grid-container">
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/userPermission')">
                用户权限管理
            </el-button>
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/systemLogs')">
                系统日志管理
            </el-button>
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/dataBackup')">
                数据备份与恢复
            </el-button>
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/systemSettings')">
                系统设置
            </el-button>
            <el-button type="primary" plain class="setting-button"
                @click="$router.push('/systemManagement/systemUpdate')">
                系统更新与维护
            </el-button>
        </el-div>
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
    color: #4A4A4A;
    /* 修改为较柔和的深灰色 */
}

.grid-container {
    display: grid;
    grid-template-columns: repeat(3, 1fr);
    /* 上方三列 */
    grid-template-rows: auto auto;
    /* 自动行数 */
    grid-gap: 15px;
    /* 设置按钮之间的间隙 */
    position: relative;
}

/* 上方的按钮 */
.setting-button {
    font-size: 20px;
    width: 300px;
    /* 固定宽度 */
    height: 300px;
    /* 固定高度，确保按钮是正方形 */
    background-color: rgba(255, 255, 255, 0.5);
    /* 透明背景 */
    color: #222;
    /* 修改为更深的文字颜色 */
    border: 2px solid rgba(255, 255, 255, 0.5);
    /* 半透明边框 */
    border-radius: 10px;
    /* 圆角 */
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.15);
    transition: all 0.3s ease-in-out;
    position: relative;
    z-index: 1;
    display: flex;
    justify-content: center;
    align-items: center;
    /* 居中文本 */
    margin: 0;
    /* 去掉按钮默认的间隙 */
}

/* 上方的按钮排布 */
.setting-button:nth-child(1),
.setting-button:nth-child(2),
.setting-button:nth-child(3) {
    grid-column: span 1;
    /* 上方三个按钮各占一列 */
}

/* 下方的按钮 */
.setting-button:nth-child(4),
.setting-button:nth-child(5) {
    grid-column: span 1;
    /* 下方两个按钮各占一列 */
    grid-row: 2;
    /* 确保下方按钮排在第二行 */
}

/* 鼠标悬停效果 */
.setting-button:hover {
    opacity: 0.85;
    transform: scale(1.05);
    /* 放大按钮，增加互动感 */
    box-shadow: 0 8px 16px rgba(0, 0, 0, 0.2);
    border-color: #ff4081;
    /* 悬浮时的边框颜色变化 */
}

/* 焦点状态 */
.setting-button:focus {
    outline: none;
    box-shadow: 0 0 10px 2px rgba(255, 64, 129, 0.5);
}

/* 响应式设计 */
@media (max-width: 768px) {
    .grid-container {
        grid-template-columns: repeat(2, 1fr);
        /* 在小屏幕上改为两列布局 */
    }
}
</style>