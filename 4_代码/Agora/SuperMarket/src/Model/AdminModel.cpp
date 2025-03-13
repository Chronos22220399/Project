//
// Created by 无铭 on 25-2-23.
//
#include <Model/AdminModel.h>
#include <Utils/DatabaseUtils.hpp>
#include <Utils/RBAC/PasswordManager.hpp>
#include <include/admin.h>
#include <sqlpp11/sqlpp11.h>

namespace Model {
// 特化出从模型到表的反射
template <> struct ReflectTable<AdminModel::Admin_, Admin::Admin> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&AdminModel::Admin_::id, &Admin::Admin::id),
        std::make_pair(&AdminModel::Admin_::username, &Admin::Admin::username),
        std::make_pair(&AdminModel::Admin_::password, &Admin::Admin::password),
        std::make_pair(&AdminModel::Admin_::role, &Admin::Admin::role));
};

template <typename AdminTableRow>
struct ReflectTableRow<AdminModel::Admin_, AdminTableRow> {
    static constexpr auto assign_model(AdminTableRow &&row) {
        return AdminModel::Admin_(
            static_cast<size_t>(row.id), std::string(row.username),
            std::string(row.password), std::string(row.role));
    }
};

struct AdminModel::AdminModelImpl
    : public GenericModel<AdminModel::Admin_, Admin::Admin> {
    AdminModelImpl() = default;
    AdminModelImpl(const AdminModelImpl &) = delete;
    ~AdminModelImpl() = default;
};

AdminModel::AdminModel()
    : impl(std::make_unique<AdminModelImpl>()),
      reg(std::make_unique<Utils::GenericRegister>(
          std::make_unique<AdminDBStrategy>(*this))) {}

std::vector<AdminModel::Admin_> AdminModel::get_all_admins() const {
    return impl->select(Admin::Admin{}.id > 0);
}

std::optional<AdminModel::Admin_> AdminModel::get_admin_by_id(size_t id) const {
    auto res = impl->select(Admin::Admin{}.id == id);
    return !res.empty() ? std::optional{res.at(0)} : std::nullopt;
}
std::optional<AdminModel::Admin_>
AdminModel::get_admin_by_username(const std::string &username) const {
    auto res = impl->select(Admin::Admin{}.username == username);
    return !res.empty() ? std::optional{res.at(0)} : std::nullopt;
}

size_t AdminModel::create_admin(const Admin_ &admin) const {
    auto res = impl->insert<Admin_>(Admin_(admin));
    return res;
}

bool AdminModel::save_to_db(std::shared_ptr<Utils::BasicUser> user) const {
    std::shared_ptr<Admin_> adminPtr = std::dynamic_pointer_cast<Admin_>(user);
    auto hashedPd = Utils::PasswordManager::hash_password(adminPtr->password);
    if (!hashedPd) {
        LOG("对管理员的密码哈希失败");
        return false;
    }
    adminPtr->password = hashedPd.value();
    auto res = impl->insert(*adminPtr);
    return res;
}

bool AdminModel::username_in_db(const std::string &username) const {
    auto res = impl->select(Admin::Admin{}.username == username);
    return res.empty();
}

AdminModel::~AdminModel() = default;

} // namespace Model
