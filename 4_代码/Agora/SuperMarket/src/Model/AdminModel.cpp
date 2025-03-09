//
// Created by 无铭 on 25-2-23.
//
#include <Model/AdminModel.h>
#include <Utils/DatabaseUtils.hpp>
#include <include/admin.h>
#include <sqlpp11/sqlpp11.h>

namespace Model {
// 特化出从模型到表的反射
template <> struct ReflectTable<AdminModel::Admin, Admin_::Admin> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&AdminModel::Admin::id, &Admin_::Admin::id),
        std::make_pair(&AdminModel::Admin::username, &Admin_::Admin::username),
        std::make_pair(&AdminModel::Admin::password, &Admin_::Admin::password));
};

template <typename AdminTableRow>
struct ReflectTableRow<AdminModel::Admin, AdminTableRow> {
    static constexpr auto assign_model(AdminTableRow &&row) {
        return AdminModel::Admin{.id = static_cast<size_t>(row.id),
                                 .username = row.username,
                                 .password = row.password};
    }
};

struct AdminModel::AdminModelImpl
    : public GenericModel<AdminModel::Admin, Admin_::Admin> {
    AdminModelImpl() = default;
    AdminModelImpl(const AdminModelImpl &) = delete;
    ~AdminModelImpl() = default;
};

AdminModel::AdminModel() = default;
std::vector<AdminModel::Admin> AdminModel::get_all_admins() const {
    return impl->select(Admin_::Admin{}.id > 0);
}

AdminModel::Admin AdminModel::get_admin_by_id(size_t id) const {
    auto res = impl->select(Admin_::Admin{}.id == id);
    return !res.empty() ? res.at(0) : Admin{};
}

AdminModel::~AdminModel() = default;

} // namespace Model
