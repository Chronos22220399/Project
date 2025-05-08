import axios from 'axios'
import { ElMessage } from 'element-plus'

const service = axios.create({
  baseURL: 'http://localhost:8080', // 根据你的后端地址修改
  timeout: 5000
})

service.interceptors.response.use(
  response => response.data,
  error => {
    ElMessage.error(error.response?.data?.message || '服务器错误')
    return Promise.reject(error)
  }
)

export default service
