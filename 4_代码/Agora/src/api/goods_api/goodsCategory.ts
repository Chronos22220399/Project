import axios from 'axios';

const API_URL = 'http://your-backend-api-url';

export const createGoodsCategory = (data: any) => {
  return axios.post(`${API_URL}/goods-category/create`, data);
};

export const getGoodsCategoryByPage = (page: number, pageSize: number) => {
  return axios.get(`${API_URL}/goods-category/getByPage`, {
    params: { page, page_size: pageSize }
  });
};

export const getAllGoodsCategories = () => {
  return axios.get(`${API_URL}/goods-category/getAll`);
};
