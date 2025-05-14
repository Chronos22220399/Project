import request from '@/utils/request'

// 仓库信息
export const getWarehouseList = () => request.get('/api/warehouse/list')
export const addWarehouse = (data: any) => request.post('/api/warehouse/add', data)
export const updateWarehouse = (id: number, data: any) => request.put(`/api/warehouse/update/${id}`, data)
export const deleteWarehouse = (id: number) => request.delete(`/api/warehouse/delete/${id}`)
// 商品入库
export const getInboundList = () => request.get('/api/inbound/list')
export const addInbound = (data: any) => request.post('/api/inbound/add', data)
export const updateInbound = (id: number, data: any) => request.put(`/api/inbound/update/${id}`, data)
export const deleteInbound = (id: number) => request.delete(`/api/inbound/delete/${id}`)
// 商品出库
export const getOutboundList = () => request.get('/api/outbound/list')
export const addOutbound = (data: any) => request.post('/api/outbound/add', data)
export const updateOutbound = (id: number, data: any) => request.put(`/api/outbound/update/${id}`, data)
export const deleteOutbound = (id: number) => request.delete(`/api/outbound/delete/${id}`)
// 库存盘点
export const getInventoryList = () => request.get('/api/inventory/list')
export const addInventory = (data: any) => request.post('/api/inventory/add', data)
export const updateInventory = (id: number, data: any) => request.put(`/api/inventory/update/${id}`, data)
export const deleteInventory = (id: number) => request.delete(`/api/inventory/delete/${id}`)
// 库存预警
export const getWarningList = () => request.get('/api/warning/list')
export const addWarning = (data: any) => request.post('/api/warning/add', data)
export const updateWarning = (id: number, data: any) => request.put(`/api/warning/update/${id}`, data)
export const deleteWarning = (id: number) => request.delete(`/api/warning/delete/${id}`)
