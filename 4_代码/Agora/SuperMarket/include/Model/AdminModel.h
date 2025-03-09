//
// Created by 无铭 on 25-2-23.
//

#ifndef ADMINMODEL_H
#define ADMINMODEL_H
#include <Model/GeneralModel.hpp>
#include <Utils/DatabaseUtils.hpp>
#include <include/admin.h>

namespace Model {

struct AdminModel {
    struct Admin {
        size_t id;
        std::string username;
        std::string password;
    };

    explicit AdminModel();
    explicit AdminModel(const Admin &admin) = delete;
    ~AdminModel();
    std::vector<Admin> get_all_admins() const;
    Admin get_admin_by_id(size_t id) const;
    size_t insert_bulk(std::vector<Admin> admins) const;

  private:
    struct AdminModelImpl;
    std::shared_ptr<AdminModelImpl> impl;
};

} // namespace Model

#endif // ADMINMODEL_H
