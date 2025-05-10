<template>
    <el-card>
        <h2>促销活动管理</h2>
        <div class="promotion-management">
            <!-- 添加促销活动表单 -->
            <el-form :model="form" ref="form" class="form-container">
                <el-form-item label="活动名称" :label-width="formLabelWidth">
                    <el-input v-model="form.name" placeholder="请输入活动名称" />
                </el-form-item>
                <el-form-item label="活动描述" :label-width="formLabelWidth">
                    <el-input v-model="form.description" placeholder="请输入活动描述" />
                </el-form-item>
                <el-form-item label="活动类型" :label-width="formLabelWidth">
                    <el-select v-model="form.type" placeholder="请选择活动类型">
                        <el-option label="折扣" value="discount" />
                        <el-option label="满减" value="full_reduction" />
                    </el-select>
                </el-form-item>
                <el-form-item label="开始时间" :label-width="formLabelWidth">
                    <el-date-picker v-model="form.start_time" type="datetime" placeholder="请选择开始时间" />
                </el-form-item>
                <el-form-item label="结束时间" :label-width="formLabelWidth">
                    <el-date-picker v-model="form.end_time" type="datetime" placeholder="请选择结束时间" />
                </el-form-item>
                <el-form-item label="状态" :label-width="formLabelWidth">
                    <el-select v-model="form.status" placeholder="请选择状态">
                        <el-option label="激活" value="active" />
                        <el-option label="已过期" value="expired" />
                        <el-option label="草稿" value="draft" />
                    </el-select>
                </el-form-item>
                <el-form-item>
                    <el-button type="primary" @click="createPromotion">添加促销活动</el-button>
                    <el-button @click="resetForm">重置</el-button>
                </el-form-item>
            </el-form>

            <!-- 促销活动表格 -->
            <h2>促销活动表格</h2>
            <el-table :data="pagedPromotions" border style="margin-top: 24px">
                <el-table-column prop="promotion_id" label="促销活动ID" />
                <el-table-column prop="name" label="促销活动名称" />
                <el-table-column prop="description" label="促销活动描述" />
                <el-table-column prop="type" label="活动类型" />
                <el-table-column prop="start_time" label="开始时间" />
                <el-table-column prop="end_time" label="结束时间" />
                <el-table-column prop="status" label="状态" />
                <el-table-column label="操作">
                    <template #default="scope">
                        <el-button size="mini" @click="editPromotion(scope.row)">编辑</el-button>
                        <el-button size="mini" class="red-button"
                            @click="removePromotion(scope.row.promotion_id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <!-- 分页 -->
            <div class="pagination">
                <el-pagination :current-page="currentPage" :page-size="pageSize" :total="totalItems"
                    @current-change="handlePageChange" @size-change="handlePageSizeChange"
                    layout="total, sizes, prev, pager, next, jumper" />
            </div>
        </div>
    </el-card>
</template>

<script>
import { ref, computed, onMounted } from 'vue';
import axios from 'axios';

export default {
    name: 'PromotionManagement',
    setup() {
        const useMock = ref(true); // 切换为 false 即使用后端接口
        const allPromotions = ref([]);
        const promotionList = ref([]);
        const currentPage = ref(1);
        const pageSize = ref(10);
        const totalItems = ref(0);

        const form = ref({
            name: '',
            description: '',
            type: 'discount',
            start_time: '',
            end_time: '',
            status: 'active'
        });

        const formLabelWidth = '120px';

        const pagedPromotions = computed(() => {
            const start = (currentPage.value - 1) * pageSize.value;
            return promotionList.value.slice(start, start + pageSize.value);
        });

        const handlePageChange = (page) => {
            currentPage.value = page;
        };

        const handlePageSizeChange = (size) => {
            pageSize.value = size;
            currentPage.value = 1;
        };

        const fetchPromotions = async () => {
            if (useMock.value) {
                const mockData = generateMockPromotions();
                promotionList.value = mockData;
                totalItems.value = mockData.length;
            } else {
                try {
                    const response = await axios.post('http://localhost:8080/api/promotion/get_by_page', {
                        page: currentPage.value,
                        page_size: pageSize.value
                    });
                    if (response.data.code === 200) {
                        promotionList.value = response.data.data.items;
                        totalItems.value = response.data.data.total;
                    }
                } catch (error) {
                    console.error(error);
                }
            }
        };

        const generateMockPromotions = () => {
            const mock = [];
            for (let i = 1; i <= 25; i++) {
                mock.push({
                    promotion_id: i,
                    name: `促销活动 ${i}`,
                    description: `描述 ${i}`,
                    type: i % 2 === 0 ? 'discount' : 'full_reduction',
                    start_time: `2025-05-${String((i % 30) + 1).padStart(2, '0')} 00:00`,
                    end_time: `2025-05-${String((i % 30) + 1).padStart(2, '0')} 23:59`,
                    status: ['active', 'expired', 'draft'][i % 3]
                });
            }
            return mock;
        };

        const createPromotion = async () => {
            if (useMock.value) {
                const newId = promotionList.value.length + 1;
                promotionList.value.push({ ...form.value, promotion_id: newId });
                totalItems.value = promotionList.value.length;
                resetForm();
            } else {
                try {
                    const response = await axios.post('http://localhost:8080/api/promotion/create', form.value);
                    if (response.data.code === 201) {
                        resetForm();
                        fetchPromotions();
                    }
                } catch (error) {
                    console.error(error);
                }
            }
        };

        const removePromotion = async (promotion_id) => {
            if (useMock.value) {
                promotionList.value = promotionList.value.filter(p => p.promotion_id !== promotion_id);
                totalItems.value = promotionList.value.length;
            } else {
                try {
                    const response = await axios.post('http://localhost:8080/api/promotion/remove', { promotion_id });
                    if (response.data.code === 200) {
                        fetchPromotions();
                    }
                } catch (error) {
                    console.error(error);
                }
            }
        };

        const resetForm = () => {
            form.value = {
                name: '',
                description: '',
                type: 'discount',
                start_time: '',
                end_time: '',
                status: 'active'
            };
        };

        const editPromotion = (row) => {
            console.log('编辑功能未实现', row);
        };

        onMounted(() => {
            fetchPromotions();
        });

        return {
            form,
            formLabelWidth,
            promotionList,
            pagedPromotions,
            currentPage,
            pageSize,
            totalItems,
            createPromotion,
            removePromotion,
            resetForm,
            editPromotion,
            handlePageChange,
            handlePageSizeChange
        };
    }
};
</script>

<style>
.promotion-management {
    padding: 20px;
}

.form-container {
    background: #f9f9f9;
    padding: 20px;
    margin-bottom: 24px;
    border-radius: 8px;
    box-shadow: 0 0 4px rgba(0, 0, 0, 0.1);
}

.pagination {
    margin-top: 16px;
    text-align: right;
}

.el-table .el-button {
    margin-right: 10px;
}

.el-table .el-button--text.red-button {
    color: red;
}
</style>
