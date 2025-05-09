<template>
    <el-card>
        <div class="promotion-management">
            <!-- 促销活动表格 -->
            <el-table :data="promotionList" border>
                <el-table-column prop="promotion_id" label="促销活动ID"></el-table-column>
                <el-table-column prop="name" label="促销活动名称"></el-table-column>
                <el-table-column prop="description" label="促销活动描述"></el-table-column>
                <el-table-column prop="type" label="活动类型"></el-table-column>
                <el-table-column prop="start_time" label="开始时间"></el-table-column>
                <el-table-column prop="end_time" label="结束时间"></el-table-column>
                <el-table-column prop="status" label="状态"></el-table-column>
                <el-table-column label="操作">
                    <template slot-scope="scope">
                        <el-button size="mini" @click="editPromotion(scope.row)">编辑</el-button>
                        <el-button size="mini" class="red-button"
                            @click="removePromotion(scope.row.promotion_id)">删除</el-button>
                    </template>
                </el-table-column>
            </el-table>

            <!-- 分页 -->
            <div class="pagination">
                <el-pagination :current-page="currentPage" :page-size="pageSize" :total="totalItems"
                    @current-change="fetchPromotions" @size-change="handlePageSizeChange">
                </el-pagination>
            </div>

            <!-- 添加促销活动按钮 -->
            <el-button type="primary" @click="openCreateDialog">新增促销活动</el-button>

            <!-- 添加促销活动弹窗 -->
            <el-dialog title="新增促销活动" :visible.sync="createDialogVisible" @close="resetForm" teleported="false">
                <el-form :model="form" ref="form">
                    <el-form-item label="活动名称" :label-width="formLabelWidth">
                        <el-input v-model="form.name" placeholder="请输入活动名称"></el-input>
                    </el-form-item>
                    <el-form-item label="活动描述" :label-width="formLabelWidth">
                        <el-input v-model="form.description" placeholder="请输入活动描述"></el-input>
                    </el-form-item>
                    <el-form-item label="活动类型" :label-width="formLabelWidth">
                        <el-select v-model="form.type" placeholder="请选择活动类型">
                            <el-option label="折扣" value="discount"></el-option>
                            <el-option label="满减" value="full_reduction"></el-option>
                        </el-select>
                    </el-form-item>
                    <el-form-item label="开始时间" :label-width="formLabelWidth">
                        <el-date-picker v-model="form.start_time" type="datetime"
                            placeholder="请选择开始时间"></el-date-picker>
                    </el-form-item>
                    <el-form-item label="结束时间" :label-width="formLabelWidth">
                        <el-date-picker v-model="form.end_time" type="datetime" placeholder="请选择结束时间"></el-date-picker>
                    </el-form-item>
                    <el-form-item label="状态" :label-width="formLabelWidth">
                        <el-select v-model="form.status" placeholder="请选择状态">
                            <el-option label="激活" value="active"></el-option>
                            <el-option label="已过期" value="expired"></el-option>
                            <el-option label="草稿" value="draft"></el-option>
                        </el-select>
                    </el-form-item>
                </el-form>

                <div slot="footer" class="dialog-footer">
                    <el-button @click="resetForm">取消</el-button>
                    <el-button type="primary" @click="createPromotion">确定</el-button>
                </div>
            </el-dialog>
        </div>
    </el-card>

</template>

<script>
import 'element-plus/dist/index.css';
import { ref, onMounted } from 'vue';
import { ElTable, ElTableColumn, ElButton, ElPagination, ElDialog, ElForm, ElFormItem, ElInput, ElSelect, ElOption, ElDatePicker } from 'element-plus';
import axios from 'axios';

export default {
    name: 'PromotionManagement',
    components: {
        ElTable,
        ElTableColumn,
        ElButton,
        ElPagination,
        ElDialog,
        ElForm,
        ElFormItem,
        ElInput,
        ElSelect,
        ElOption,
        ElDatePicker
    },
    setup() {

        const promotionList = ref([]);
        const currentPage = ref(1);
        const pageSize = ref(10);
        const totalItems = ref(0);
        const createDialogVisible = ref(false);
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
                const response = await axios.post('/api/promotion/get_by_page', {
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
                const response = await axios.post('/api/promotion/remove', { promotion_id });
                if (response.data.code === 200) {
                    fetchPromotions();
                }
            } catch (error) {
                console.error(error);
            }
        };

        const openCreateDialog = () => {
            console.log('Opening create dialog...');
            createDialogVisible.value = true;  // 弹窗应该在点击时显示
            console.log("状态:", createDialogVisible.value); // 应该是 true
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
                const response = await axios.post('/api/promotion/create', form.value);
                if (response.data.code === 201) {
                    createDialogVisible.value = false;
                    fetchPromotions();
                }
            } catch (error) {
                console.error(error);
            }
        };

        onMounted(() => {
            fetchPromotions();
        });

        return {
            promotionList,
            currentPage,
            pageSize,
            totalItems,
            createDialogVisible,
            form,
            formLabelWidth,
            fetchPromotions,
            removePromotion,
            openCreateDialog,
            resetForm,
            createPromotion
        };
    }
};
</script>

<style>
.promotion-management {
    padding: 20px;
}

.pagination {
    margin-top: 16px;
    text-align: right;
}

.el-table .el-button {
    margin-right: 10px;
}

.el-table .el-button--text {
    color: #409EFF;
}

.el-table .el-button--text.red-button {
    color: red;
}

.dialog-footer {
    display: flex;
    justify-content: flex-end;
}
</style>