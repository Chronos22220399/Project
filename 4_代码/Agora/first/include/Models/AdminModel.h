//
// Created by 无铭 on 25-2-23.
//

#ifndef ADMINMODEL_H
#define ADMINMODEL_H
#include <include/admin.h>
#include <utils/database_utils/database_utils.hpp>
#include <utils/database_utils/database_query.hpp>


struct AdminModel : utils::database_utils::ConnDefiner {
    using size_type = size_t;

    struct Admin {
        int id;
        std::string username;
        std::string password;
        Admin() = default;
        Admin(const int id_, std::string username_, std::string password_)
            : id(id_), username(std::move(username_)),
              password(std::move(password_)) {}
    };


    explicit AdminModel();
    explicit AdminModel(const Admin &admin) = delete;
    size_type create(const Admin &admin) const;
    [[nodiscard]] std::vector<Admin> get_all_admins() const;
    [[nodiscard]] std::vector<Admin> get_admin_by_id(int id) const;
    [[nodiscard]] std::vector<Admin>
    get_admin_by_username(const std::string &name) const;
    [[nodiscard]] std::vector<Admin> get_admin_by_id_range(int lbound,
                                                           int rbound) const;
    [[nodiscard]] std::vector<Admin> get_admin_test() const;
    [[nodiscard]] std::vector<Admin> get_admin_by_username_test(const std::string& username) const;
    ~AdminModel();

  // private:
    struct AdminModelImpl;
    std::unique_ptr<AdminModelImpl> impl;
};

template <typename TableRow> struct utils::database_utils::DataTypeTraits<TableRow, AdminModel::Admin> {
    static AdminModel::Admin get_args(const TableRow &row) {
        return AdminModel::Admin(row.id, row.username, row.password);
    }
};
#endif // ADMINMODEL_H
