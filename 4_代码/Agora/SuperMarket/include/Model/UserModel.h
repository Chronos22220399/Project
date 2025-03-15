//
// Created by 无铭 on 25-2-23.
//

#ifndef ADMINMODEL_H
#define ADMINMODEL_H
#include <Model/GeneralModel.hpp>
#include <Utils/DatabaseUtils.hpp>
#include <Utils/RBAC/BasicUser.hpp>
#include <Utils/RBAC/Register.h>
#include <include/user.h>
#include <optional>

namespace Model {

struct AdminModel {
    struct Admin_ : public Utils::BasicUser {
        Admin_() = default;
        explicit Admin_(size_t id, const std::string &username,
                        const std::string &password, const std::string &role)
            : BasicUser(id, username, password, role) {}
    };

    struct AdminDBStrategy final : Utils::RegDBStrategy {
        explicit AdminDBStrategy(const AdminModel &model) : model_(model) {}
        ~AdminDBStrategy() = default;
        bool save_to_db(std::shared_ptr<Utils::BasicUser> user) const {
            return model_.save_to_db(user);
        }
        bool username_in_db(const std::string &username) const {
            return model_.username_in_db(username);
        }

      private:
        const AdminModel &model_;
    };

    explicit AdminModel();

    explicit AdminModel(const AdminModel &admin) = delete;

    ~AdminModel();

    std::vector<Admin_> get_all_admins() const;

    std::optional<Admin_> get_admin_by_id(size_t id) const;

    std::optional<Admin_>
    get_admin_by_username(const std::string &username) const;

    size_t create_admin(const Admin_ &admin) const;

    bool save_to_db(std::shared_ptr<Utils::BasicUser> user) const;

    bool username_in_db(const std::string &username) const;

  private:
    struct AdminModelImpl;
    std::unique_ptr<AdminModelImpl> impl;
    std::unique_ptr<Utils::GenericRegister> reg;
};

} // namespace Model

#endif // ADMINMODEL_H
