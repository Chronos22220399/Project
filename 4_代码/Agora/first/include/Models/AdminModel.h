//
// Created by 无铭 on 25-2-23.
//

#ifndef ADMINMODEL_H
#define ADMINMODEL_H
#include <include/admin.h>
#include <utils/database_utils.hpp>

struct AdminModel : utils::ConnDefiner {
    struct Admin {
        int id;
        std::string username;
        std::string password;
        Admin() = default;
        Admin(const int id_, std::string username_, std::string password_)
            : id(id_), username(std::move(username_)),
              password(std::move(password_)) {}
    };

    explicit AdminModel(conn_pool_ptr_type conn_pool_ptr);
    explicit AdminModel(const Admin &admin) = delete;
    [[nodiscard]] std::vector<Admin> get_all_admins() const;
    [[nodiscard]] std::vector<Admin> get_admin_by_id(int id) const;
    [[nodiscard]] std::vector<Admin>
    get_admin_by_username(const std::string &name) const;
    [[nodiscard]] std::vector<Admin> get_admin_by_id_range(int lbound,
                                                           int rbound) const;
    [[nodiscard]] std::vector<Admin> get_admin_test() const;
    ~AdminModel();

  private:
    struct AdminModelImpl;
    std::unique_ptr<AdminModelImpl> impl;
};

#endif // ADMINMODEL_H
