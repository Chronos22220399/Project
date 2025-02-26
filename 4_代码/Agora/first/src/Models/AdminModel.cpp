//
// Created by 无铭 on 25-2-23.
//
#include <Models/AdminModel.h>
#include <sqlpp11/sqlpp11.h>
#include <utils/database_utils/database_utils.hpp>
#include <include/admin.h>

struct AdminModel::AdminModelImpl : utils::database_utils::DataBaseHelper {
    explicit AdminModelImpl()
        : DataBaseHelper() {}

    // create
    [[nodiscard]] size_t create(const Admin &admin) const {
        return DataBaseHelper::execute<size_t>([](const ConnDefiner::pooled_conn_ptr_type& conn, const Admin& admin_) {
            Admin_::Admin _admin {};
            (*conn)(insert_into(_admin).set(_admin.username=admin_.username, _admin.password=admin_.password));
            return static_cast<size_t>(1);
        }, admin);
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
        return execute<std::vector<Admin>>(query,
                                           std::forward<Value>(value));
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
        return execute<std::vector<Admin>>(query,
                                           std::forward<Table>(table),
                                           std::forward<Condition>(condition));
    }

    // ------ test ----- //
    std::vector<Admin> get_admin_by_username_test(const std::string &name) const {
        utils::database_utils::GenericDataGetter<Admin> getter;
        Admin_::Admin admin_;
        auto res = getter.get_data<decltype(admin_)>(std::move(admin_), admin_.username == "helo");
        for (const auto &item : res) {
            fmt::print("{} {}\n", item.username, item.password);
        }
        return res;
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

[[nodiscard]] std::vector<AdminModel::Admin>
AdminModel::get_admin_test() const {
    Admin_::Admin admin;
    auto condition = (admin.id == 1);
    return impl->get_admin_by_generic_condition(admin, condition);
}

[[nodiscard]] std::vector<AdminModel::Admin> AdminModel::get_admin_by_username_test(const std::string& username) const {
    return impl->get_admin_by_username_test(username);
}

AdminModel::~AdminModel() = default;
