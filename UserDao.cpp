#include "UserDao.h"

int UserDao::getIndexByUsername(string username) throw(runtime_error) {
    for (int i = 0; i < usersPtr->size(); i++) {
        if (usersPtr->at(i).getUsername() == username)
            return i;
    }

    throw runtime_error("不能找到用户名为"+username+"的用户");
}

bool UserDao::existByUsername(string username) {
    try {
        getIndexByUsername(username);
        return true;
    }
    catch (runtime_error& e) {
        return false;
    }
}

void UserDao::addUser(const User& user) throw(invalid_argument) {
    if (existByUsername(user.getUsername())) {
        throw invalid_argument("用户名为"+user.getUsername()+"的用户，无法添加");
    }

    usersPtr->push_back(user);
}

void UserDao::deleteUser(string username) {
    int index = getIndexByUsername(username);

    vector<User> backup = *usersPtr;
    *usersPtr = vector<User>();
    for (int i = 0; i < backup.size(); i++) {
        if (i != index)
            usersPtr->push_back(backup[i]);
    }
}

void UserDao::updateUser(const User& user) {
    int index = getIndexByUsername(user.getUsername());
    (*usersPtr)[index]=user;
}

User UserDao::getUser(string username) {
    int index = getIndexByUsername(username);
    return usersPtr->at(index);
}

vector<User> UserDao::getAllUsers(){
    return *usersPtr;
}


