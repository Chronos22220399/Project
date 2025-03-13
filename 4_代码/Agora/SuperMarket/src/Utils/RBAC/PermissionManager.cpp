#include "../include/Utils/RBAC/PermissionManager.h"
#include "../include/Utils/Log.hpp"
#include <fstream>
#include <mutex>
#include <shared_mutex>

namespace Utils {

void to_json(nlohmann::json &j, const Permission &p) {
    using json = nlohmann::json;
    j = json{{p.resource, json::array()}};
    for (auto &action : p.actions) {
        j[p.resource].push_back(actionToString(action));
    }
}

class PermissionManager::PMImpl {
    struct PermissionStorage {
        static void load_from_json() {
            using namespace nlohmann;
            std::ifstream jfile("./SuperMarket/datas/permissions.json");
            json j;
            jfile >> j;

            role_permissions.clear();
            for (auto &[role, permissions] : j.items()) { // 遍历角色
                for (auto &[resource, actions] : permissions.items()) {
                    Permission temp;
                    temp.resource = resource;
                    for (const auto &action : actions) {
                        temp.actions.insert(stringToAction(action));
                    }
                    role_permissions[role].insert(std::move(temp));
                }
            }
        }

        static void save_to_json() {
            using namespace nlohmann;
            json j;
            for (auto &[role, permissions] : role_permissions) {
                j[role] = permissions;
            }
            std::ofstream jfile("./SuperMarket/datas/permissions.json");
            jfile << j.dump(4);
        }
    };

  public:
    PMImpl() { load_from_json(); }

    void load_from_json() {
        std::shared_lock<std::shared_mutex> lock(rw_mutex);
        PermissionStorage::load_from_json();
    }

    void save_to_json() {
        std::shared_lock<std::shared_mutex> lock(rw_mutex);
        PermissionStorage::save_to_json();
    }

    bool check_access(const BasicUser &user, const std::string &resource,
                      Action action) const {
        // 读锁
        std::shared_lock<std::shared_mutex> lock(rw_mutex);
        auto it = role_permissions.find(user.role);
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
        std::shared_lock<std::shared_mutex> lock(rw_mutex);
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

bool PermissionManager::check_access(const BasicUser &user,
                                     const Resource &resource,
                                     Action action) const {
    auto resourceStr = resourceToString(resource);
    return impl->check_access(user, resourceStr, action);
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

void PermissionManager::load_from_json() { impl->load_from_json(); }

void PermissionManager::save_to_json() { impl->save_to_json(); }
} // namespace Utils
