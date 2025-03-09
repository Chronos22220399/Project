#include <Utils/Log.hpp>
#include <Utils/RBAC/PermissionManager.h>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>

namespace Utils {

// 将字符串转换为 `Action` 枚举
Action stringToAction(const std::string &actionStr) {
    if (actionStr == "Read")
        return Action::Read;
    if (actionStr == "Write")
        return Action::Write;
    if (actionStr == "Delete")
        return Action::Delete;
    throw std::invalid_argument("Unknown action: " + actionStr);
}

std::string actionToString(Action action) {
    if (action == Action::Read)
        return "Read";
    if (action == Action::Write)
        return "Write";
    if (action == Action::Delete)
        return "Delete";
    throw std::invalid_argument("Unknown action");
}

void to_json(nlohmann::json &j, const Permission &p) {
    using json = nlohmann::json;
    j = json{{p.resource, json::array()}};
    for (auto &action : p.actions) {
        j[p.resource].push_back(actionToString(action));
    }
}

void from_json(const nlohmann::json &j, Permission &p) {
    auto it = j.begin();
    p.resource = it.key();
    for (const auto &actionStr : it.value()) {
        p.actions.insert(stringToAction(actionStr));
    }
}

class PermissionManager::PMImpl {
  public:
    PMImpl() { load_data_from_json(); }

    void load_data_from_json() {
        using namespace nlohmann;
        std::unique_lock<std::shared_mutex> lock(rw_mutex);
        std::ifstream jfile("./SuperMarket/datas/permissions.json");
        json j;
        jfile >> j;

        role_permissions.clear();
        for (auto &[role, resources] : j.items()) {
            for (auto &resource_entry : resources) {
                for (auto &[resource, actions] : resource_entry.items()) {
                    if (actions.is_array()) {
                        std::unordered_set<Action> actions_;
                        for (auto &action : actions) {
                            actions_.insert(stringToAction(action));
                        }
                        Permission p{resource, std::move(actions_)};
                        role_permissions[role].insert(p);
                    } else {
                        throw std::runtime_error(
                            "permission.json 内出现格式错误，请检查是否有非 "
                            "array "
                            "的 actions");
                    }
                }
            }
        }
    }

    void save_data_to_json() {
        std::shared_lock lock(rw_mutex);
        using namespace nlohmann;
        json j;
        for (auto &[role, permissions] : role_permissions) {
            j[role] = permissions;
        }

        std::ofstream jfile("./SuperMarket/datas/permissions.json");
        jfile << j.dump(4);
    }

    bool check_access(const std::unique_ptr<BasicUser> &user,
                      const std::string &resource, Action action) const {
        // 读锁
        std::shared_lock<std::shared_mutex> lock(rw_mutex);
        auto it = role_permissions.find(user->role);
        if (it == role_permissions.end()) {
            return false;
        }
        for (const auto &permission : it->second) {
            if (permission.resource == resource) {
                for (const auto &action_ : permission.actions) {
                    if (action_ == action) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void display() const {
        for (const auto &[role, permissions] : role_permissions)
            for (auto &permission : permissions) {
                for (auto &action : permission.actions) {
                    LOG("Role: {}, Resource: {}, Action: {}", role,
                        permission.resource, actionToString(action));
                }
            }
    }

    std::unordered_set<Permission>
    get_permission_of(const std::string &role) const {
        std::shared_lock<std::shared_mutex> lock(rw_mutex);
        auto it = role_permissions.find(role);
        if (it == role_permissions.end()) {
            return {};
        }
        return it->second;
    }

    bool set_actions_of(const std::string &role, const std::string &resource,
                        const std::unordered_set<Action> &newActions) {
        std::unique_lock<std::shared_mutex> lock(rw_mutex);
        auto it_rp = role_permissions.find(role);
        if (it_rp == role_permissions.end()) {
            role_permissions[role].insert(Permission{resource, newActions});
            return true;
        }
        auto &permissions = it_rp->second;
        for (auto it = permissions.begin(); it != permissions.end();) {
            if (it->resource == resource) {
                // 创建新权限对象
                Permission new_perm{it->resource, newActions};

                it = permissions.erase(it);
                permissions.insert(new_perm);
                return true;
            } else {
                it++;
            }
        }
        return false;
    }

    ~PMImpl() = default;

  private:
    static std::unordered_map<std::string, std::unordered_set<Permission>>
        role_permissions;
    mutable std::shared_mutex rw_mutex;
};

std::unordered_map<std::string, std::unordered_set<Permission>>
    PermissionManager::PMImpl::role_permissions;

PermissionManager::PermissionManager() : impl(std::make_unique<PMImpl>()) {}

PermissionManager::~PermissionManager() = default;

bool PermissionManager::check_access(const std::unique_ptr<BasicUser> &user,
                                     const std::string &resource,
                                     Action action) const {
    return impl->check_access(user, resource, action);
}

void PermissionManager::display() const { impl->display(); }

std::unordered_set<Permission>
PermissionManager::get_permission_of(const std::string &role) const {
    return impl->get_permission_of(role);
}

bool PermissionManager::set_actions_of(
    const std::string &role, const std::string &resource,
    const std::unordered_set<Action> &newActions) {
    return impl->set_actions_of(role, resource, newActions);
}

void PermissionManager::load_data_from_json() { impl->load_data_from_json(); }

void PermissionManager::save_data_to_json() { impl->save_data_to_json(); }
} // namespace Utils
