//
// Created by 无铭 on 25-3-10.
//

#ifndef BASICUSER_H
#define BASICUSER_H
#include <string>

namespace Utils {

struct BasicUser {
    size_t id;
    std::string username;
    std::string password;
    std::string role;

    BasicUser() = default;
    BasicUser(size_t id, const std::string &username, const std::string &password, const std::string& role): id(id), username(username), password(password), role(role) {}
};

}
#endif //BASICUSER_H
