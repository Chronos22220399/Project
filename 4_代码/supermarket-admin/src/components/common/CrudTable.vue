<!-- <template>
    <el-card>
        <div class="toolbar" v-if="showAddButton">
            <el-button type="primary" @click="openDialog()">{{ addButtonText }}</el-button>
        </div>

        <el-table :data="paginatedData" border style="width: 100%">
            <el-table-column v-for="col in columns" :key="col.prop" :prop="col.prop" :label="col.label"
                :width="col.width" v-bind="col.attrs">
                <template v-if="col.slot" #default="scope">
                    <component :is="col.slot" :row="scope.row" :index="scope.$index" />
                </template>
            </el-table-column>

            <el-table-column v-if="showOperations" label="操作" width="180">
                <template #default="scope">
                    <el-button size="small" @click="openDialog(scope.row)">{{ editButtonText }}</el-button>
                    <el-button size="small" type="danger" @click="handleDelete(scope.row[idKey])">删除</el-button>
                </template>
            </el-table-column>
        </el-table>

        <el-pagination v-if="tableData.length > pageSize" :current-page="currentPage" :page-size="pageSize"
            :total="tableData.length" @current-change="handlePageChange" layout="prev, pager, next, jumper" />

        <el-dialog :title="dialogTitle" v-model="dialogVisible" :destroy-on-close="true">
            <el-form :model="form" :rules="rules" ref="formRef" label-width="120px">
                <template v-for="field in formFields" :key="field.prop">
                    <el-form-item :label="field.label" :prop="field.prop" :rules="field.rules || []">
                        <component :is="field.component || 'el-input'" v-model="form[field.prop]" v-bind="field.attrs">
                            <template v-if="field.options" #default>
                                <el-option v-for="opt in field.options" :key="opt.value" :label="opt.label"
                                    :value="opt.value" />
                            </template>
                        </component>
                    </el-form-item>
                </template>
            </el-form>
            <template #footer>
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="handleSave">保存</el-button>
            </template>
        </el-dialog>
    </el-card>
</template>

<script setup lang="ts">
import { ref, computed, reactive, toRefs } from 'vue'
import axios from 'axios'

/**
 * props:
 * - apiBaseUrl: CRUD 请求的基础 URL，后续拼接 id 等
 * - columns: 表格列配置数组，元素结构 { prop, label, width?, slot?, attrs? }
 * - formFields: 表单字段配置数组，元素结构 { prop, label, component?, attrs?, options?, rules? }
 * - idKey: 唯一标识字段名，默认 'id'
 * - addButtonText / editButtonText: 按钮文本
 * - showAddButton / showOperations: 控制添加按钮和操作列是否显示
 */

defineProps<{
    apiBaseUrl: string
    columns: Array<{
        prop: string
        label: string
        width?: string | number
        slot?: any
        attrs?: object
    }>
    formFields: Array<{
        prop: string
        label: string
        component?: any
        attrs?: object
        options?: Array<{ label: string; value: any }>
        rules?: Array<object>
    }>
    idKey?: string
    addButtonText?: string
    editButtonText?: string
    showAddButton?: boolean
    showOperations?: boolean
}>()

const props = withDefaults(defineProps(), {
    idKey: 'id',
    addButtonText: '添加',
    editButtonText: '编辑',
    showAddButton: true,
    showOperations: true
})

const tableData = ref<any[]>([]) // 初始可以为空，外部通过接口请求赋值
const dialogVisible = ref(false)
const dialogTitle = ref('')
const form = reactive<Record<string, any>>({})
const currentPage = ref(1)
const pageSize = ref(10)
const formRef = ref()

const paginatedData = computed(() => {
    const start = (currentPage.value - 1) * pageSize.value
    return tableData.value.slice(start, start + pageSize.value)
})

const openDialog = (row?: any) => {
    dialogTitle.value = row ? `${props.editButtonText}信息` : `${props.addButtonText}信息`
    Object.assign(form, row ? { ...row } : {})
    dialogVisible.value = true
}

const handleSave = () => {
    formRef.value.validate(async valid => {
        if (!valid) return

        try {
            let response
            if (form[props.idKey!]) {
                response = await axios.put(`${props.apiBaseUrl}/${form[props.idKey!]}`, form)
                // 更新本地数据
                const idx = tableData.value.findIndex(item => item[props.idKey!] === form[props.idKey!])
                if (idx !== -1) tableData.value[idx] = { ...form }
            } else {
                response = await axios.post(props.apiBaseUrl, form)
                // 新增本地数据，假设返回id在response.data[props.idKey]
                const newId = response.data[props.idKey!] || Date.now()
                tableData.value.push({ ...form, [props.idKey!]: newId })
            }
            dialogVisible.value = false
        } catch (error) {
            console.error('保存失败', error)
        }
    })
}

const handleDelete = async (id: string | number) => {
    try {
        await axios.delete(`${props.apiBaseUrl}/${id}`)
        tableData.value = tableData.value.filter(item => item[props.idKey!] !== id)
    } catch (error) {
        console.error('删除失败', error)
    }
}

const handlePageChange = (page: number) => {
    currentPage.value = page
}

// 这里你可以在父组件调用后设置 tableData.value，比如请求接口数据后赋值
</script>

<style scoped>
.toolbar {
    margin-bottom: 12px;
}
</style> -->
