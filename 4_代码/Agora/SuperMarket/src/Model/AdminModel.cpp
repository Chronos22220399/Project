//
// Created by 无铭 on 25-2-23.
//
#include <Model/AdminModel.h>
#include <Utils/DatabaseUtils.hpp>
#include <include/admin.h>
#include <sqlpp11/sqlpp11.h>

struct AdminModel::AdminModelImpl : utils::DataBaseHelper {
    explicit AdminModelImpl() : DataBaseHelper() {}

    // create
    [[nodiscard]] size_t create(const Admin &admin) const {
        return DataBaseHelper::execute<size_t>(
            [](const ConnDefiner::pooled_conn_ptr_type &conn,
               const Admin &admin_) {
                Admin_::Admin _admin{};
                (*conn)(
                    insert_into(_admin).set(_admin.username = admin_.username,
                                            _admin.password = admin_.password));
                return static_cast<size_t>(1);
            },
            admin);
    }

    // read
    [[nodiscard]] std::vector<Admin> get_all_admins() const {
        auto query = [](const pooled_conn_ptr_type &conn) {
            Admin_::Admin admin;
            std::vector<Admin> ret;
            for (const auto &row :
                 (*conn)(select(admin.id, admin.username, admin.password)
                             .from(admin)
                             .where(admin.id > 0))) {
                ret.emplace_back(row.id, row.username, row.password);
            }
            return ret;
        };
        return execute<std::vector<Admin>>(query);
    }

    template <typename Table, typename Condition>
    [[nodiscard]] std::vector<Admin>
    get_admin_by_generic_condition(Table &&table, Condition &&condition) const {
        auto query = [](const pooled_conn_ptr_type &conn_, Table &&table_,
                        Condition &&condition_) {
            auto res =
                (*conn_)(select(all_of(table_))
                             .from(table_)
                             .where(std::forward<Condition>(condition_)));
            std::vector<Admin> ret_admin{};
            for (const auto &row : res) {
                ret_admin.emplace_back(row.id, row.username, row.password);
            }
            return ret_admin;
        };
        return execute<std::vector<Admin>>(query, std::forward<Table>(table),
                                           std::forward<Condition>(condition));
    }

    template <typename ColumnPtr, typename Value>
    [[nodiscard]] std::vector<Admin> get_admin_generic_by(Value &&value) const {
        auto query = [](const pooled_conn_ptr_type &conn, Value &&value_) {
            Admin_::Admin admin;
            ColumnPtr column_ptr{};
            auto res = (*conn)(
                select(admin.id, admin.username, admin.password)
                    .from(admin)
                    .where(admin.*column_ptr == std::forward<Value>(value_)));
            std::vector<Admin> ret_admin{};
            for (const auto &row : res) {
                ret_admin.emplace_back(row.id, row.username, row.password);
            }
            return ret_admin;
        };
        return execute<std::vector<Admin>>(query, std::forward<Value>(value));
    }

    // update
    template <typename ColumnPtr, typename CmpValue>
    size_type update_generic(CmpValue &&cmpd_value, const Admin &admin) {
        auto updater = [](pooled_conn_ptr_type conn, const CmpValue &cmpd_value,
                          const Admin &admin) {
            Admin_::Admin admin_;
            ColumnPtr column_ptr{};
            auto res = (*conn)(update(admin_)
                                   .set(admin_.username = admin.username,
                                        admin_.password = admin.password)
                                   .where(admin_.*column_ptr ==
                                          std::forward<CmpValue>(cmpd_value)));
            return 1;
        };
        return execute<size_type>(updater, cmpd_value, admin);
    }

    // remove
    // TODO: 后续可以考虑将 remove 和 update 的返回值都改为
    // std::vector<Admin>，其内部存放原本的值，为空表明处理失败，此外还要注意不存在的情况，此时必定失败
    template <typename ColumnPtr, typename CmpValue>
    size_type remove_generic(CmpValue &&cmpd_value) {
        auto updater = [](pooled_conn_ptr_type conn,
                          const CmpValue &cmpd_value) {
            Admin_::Admin admin_;
            ColumnPtr column_ptr{};
            auto res = (*conn)(remove_from(admin_).where(
                admin_.*column_ptr == std::forward<CmpValue>(cmpd_value)));
            return 1;
        };
        return execute<size_type>(updater, cmpd_value);
    }

    ~AdminModelImpl() = default;
};

AdminModel::AdminModel() = default;

AdminModel::size_type AdminModel::create(const Admin &admin) const {
    return impl->create(admin);
}

[[nodiscard]] std::vector<AdminModel::Admin>
AdminModel::get_all_admins() const {
    return impl->get_all_admins();
}

[[nodiscard]] std::vector<AdminModel::Admin>
AdminModel::get_admin_by_id(const int id) const {
    return impl->get_admin_generic_by<decltype(&Admin_::Admin::id)>(id);
}

[[nodiscard]] std::vector<AdminModel::Admin>
AdminModel::get_admin_by_username(const std::string &username) const {
    return impl->get_admin_generic_by<decltype(&Admin_::Admin::username)>(
        username);
}

[[nodiscard]] std::vector<AdminModel::Admin>
AdminModel::get_admin_by_id_range(int lbound, int rbound) const {
    if (lbound >= rbound) {
        throw std::invalid_argument(FORMAT_LOG_STR("Invalid range"));
    }
    Admin_::Admin admin;
    auto condition = (admin.id >= lbound && admin.id < rbound);
    return impl->get_admin_by_generic_condition(admin, condition);
}

// delete
AdminModel::size_type
AdminModel::update_by_username(const std::string &ori_username,
                               const Admin &admin) {
    return impl->update_generic<decltype(&Admin_::Admin::username)>(
        ori_username, admin);
}

AdminModel::size_type AdminModel::update_by_id(const size_t id,
                                               const Admin &admin) {
    return impl->update_generic<decltype(&Admin_::Admin::id)>(id, admin);
}

// delete
AdminModel::size_type
AdminModel::delete_by_username(const std::string &username) const {
    return impl->remove_generic<decltype(&Admin_::Admin::username)>(username);
}

AdminModel::size_type AdminModel::delete_by_id(size_type id) const {
    return impl->remove_generic<decltype(&Admin_::Admin::id)>(id);
}

AdminModel::~AdminModel() = default;
