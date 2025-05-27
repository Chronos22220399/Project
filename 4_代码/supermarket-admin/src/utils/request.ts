import axios from 'axios'

// 创建 axios 实例
const request = axios.create({
  baseURL: import.meta.env.VITE_API_BASE_URL || 'http://localhost:8080/api', // 默认请求基础路径
  timeout: 5000,
})

// 请求拦截器（可选）
// request.interceptors.request.use(config => {
//   // 这里可以加token等
//   return config
// })

// 响应拦截器（可选）
// request.interceptors.response.use(response => response.data, error => Promise.reject(error))

export default request
