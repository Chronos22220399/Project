import axios from 'axios';

const API_URL = 'http://your-backend-api-url';

export const createGoodsPrice = (data: any) => {
  return axios.post(`${API_URL}/goods-price/create`, data);
};

export const updateGoodsPrice = (data: any) => {
  return axios.put(`${API_URL}/goods-price/updateByGoodsId`, data);
};

export const deleteGoodsPrice = (goodsId: string) => {
  return axios.delete(`${API_URL}/goods-price/removeByGoodsId`, {
    data: { goods_id: goodsId }
  });
};

export const getGoodsPriceByPage = (page: number, pageSize: number) => {
  return axios.get(`${API_URL}/goods-price/getByPage`, {
    params: { page, page_size: pageSize }
  });
};
