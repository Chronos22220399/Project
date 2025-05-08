import axios from 'axios';

const API_URL = 'http://your-backend-api-url'; // 替换为后端接口地址

export const createPromotion = (data: any) => {
  return axios.post(`${API_URL}/promotion/create`, data);
};

export const getPromotionsByPage = (page: number, pageSize: number) => {
  return axios.get(`${API_URL}/promotion/getByPage`, {
    params: { page, page_size: pageSize }
  });
};

export const getAllPromotions = () => {
  return axios.get(`${API_URL}/promotion/getAll`);
};
