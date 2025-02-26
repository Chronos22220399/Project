//
// Created by 无铭 on 25-2-23.
//

#ifndef ADMINMODEL_H
#define ADMINMODEL_H
#include <include/admin.h>
#include <utils/database_utils/database_query.hpp>
#include <utils/database_utils/database_utils.hpp>

struct AdminModel : utils::database_utils::ConnDefiner {
    struct Admin;
    using size_type = size_t;
    using data_type = std::vector<Admin>;

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
    // create
    size_type create(const Admin &admin) const;
    // read
    [[nodiscard]] data_type get_all_admins() const;
    [[nodiscard]] data_type get_admin_by_id(int id) const;
    [[nodiscard]] data_type
    get_admin_by_username(const std::string &name) const;
    [[nodiscard]] data_type get_admin_by_id_range(int lbound, int rbound) const;
    [[nodiscard]] data_type get_admin_test() const;
    [[nodiscard]] data_type
    get_admin_by_username_test(const std::string &username) const;
    // update
    // if update failed return 0, else return 1
    size_type update_by_username(const std::string &ori_username,
                                 const Admin &admin);
    size_type update_by_id(const std::string &ori_username, const Admin &admin);
    // delete
    size_type delete_by_username(const std::string &username) const;
    size_type delete_by_id(size_type id) const;
    ~AdminModel();

  private:
    struct AdminModelImpl;
    std::unique_ptr<AdminModelImpl> impl;
};

// used by GenericGetter
template <typename TableRow>
struct utils::database_utils::DataTypeTraits<TableRow, AdminModel::Admin> {
    static AdminModel::Admin get_args(const TableRow &row) {
        return AdminModel::Admin(row.id, row.username, row.password);
    }
};
#endif // ADMINMODEL_H
