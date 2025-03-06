//
// Created by 无铭 on 25-2-23.
//

#ifndef ADMINMODEL_H
#define ADMINMODEL_H
#include <Utils/DatabaseUtils.hpp>
#include <include/admin.h>
#include <Model/GeneralModel.hpp>

namespace Model
{

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

private:
    struct AdminModelImpl;
    std::shared_ptr<AdminModelImpl> impl;
};


}

#endif // ADMINMODEL_H