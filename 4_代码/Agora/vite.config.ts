import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vite.dev/config/
export default defineConfig({
  plugins: [vue()],
  server: {
    proxy: {
      '/api': {
        target: 'http://localhost:8080', // 后端服务器地址
        changeOrigin: true, // 对于跨域请求设置为true
        secure: false,      // 如果后端是 https ，则设置为 false
        rewrite: (path) => path.replace(/^\/api/, ''), // 将路径中的 /api 前缀去除
      },
    },
  },
})
