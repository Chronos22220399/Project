//
// Created by 无铭 on 25-2-23.
//

#ifndef ADMINMODEL_H
#define ADMINMODEL_H
#include <Model/GeneralModel.hpp>
#include <Utils/DatabaseUtils.hpp>
#include <include/admin.h>
#include <Utils/RBAC/BasicUser.hpp>

namespace Model {

struct AdminModel {
    struct Admin_: public Utils::BasicUser {
        Admin_() = default;
        explicit Admin_(size_t id, const std::string &username, const std::string &password, const std::string &role): BasicUser(id, username, password, role) {}
    };

    explicit AdminModel();
    explicit AdminModel(const Admin_ &admin) = delete;
    ~AdminModel();
    std::vector<Admin_> get_all_admins() const;
    std::optional<Admin_> get_admin_by_id(size_t id) const;
    std::optional<Admin_> get_admin_by_username(const std::string &username) const;
    size_t create_admin(const Admin_ &admin) const;



    size_t insert_bulk(std::vector<Admin_> admins) const;

  private:
    struct AdminModelImpl;
    std::shared_ptr<AdminModelImpl> impl;
};

} // namespace Model

#endif // ADMINMODEL_H
