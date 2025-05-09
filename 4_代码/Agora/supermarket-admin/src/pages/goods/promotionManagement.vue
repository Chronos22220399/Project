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
            <el-table :data="promotionList" border style="margin-top: 24px">
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
                    @current-change="fetchPromotions" @size-change="handlePageSizeChange" />
            </div>
        </div>
    </el-card>
</template>

<script>
import { ref, onMounted } from 'vue';
import axios from 'axios';

export default {
    name: 'PromotionManagement',
    setup() {
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

        const fetchPromotions = async (page = 1, size = 10) => {
            try {
                const response = await axios.post('http://localhost:8080/api/promotion/get_by_page', {
                    page,
                    page_size: size
                });
                if (response.data.code === 200) {
                    promotionList.value = response.data.data.items;
                    totalItems.value = response.data.data.total;
                }
            } catch (error) {
                console.error(error);
            }
        };

        const removePromotion = async (promotion_id) => {
            try {
                const response = await axios.post('http://localhost:8080/api/promotion/remove', { promotion_id });
                if (response.data.code === 200) {
                    fetchPromotions();
                }
            } catch (error) {
                console.error(error);
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

        const createPromotion = async () => {
            try {
                const response = await axios.post('http://localhost:8080/api/promotion/create', form.value);
                if (response.data.code === 201) {
                    resetForm();
                    fetchPromotions();
                }
            } catch (error) {
                console.error(error);
            }
        };

        const editPromotion = (row) => {
            console.log('编辑功能未实现', row);
        };

        onMounted(() => {
            fetchPromotions();
        });

        return {
            promotionList,
            currentPage,
            pageSize,
            totalItems,
            form,
            formLabelWidth,
            fetchPromotions,
            removePromotion,
            resetForm,
            createPromotion,
            editPromotion
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
