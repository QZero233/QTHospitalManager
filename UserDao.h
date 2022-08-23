#ifndef USERDAO_H
#define USERDAO_H


#include "DataSource.h"

class UserDao
{
public:
    UserDao(){
        DataSource* dataSourcePtr=DataSource::getInstance();
        usersPtr=dataSourcePtr->getUsersPtr();
    }

    int getIndexByUsername(string username) throw(runtime_error);
    bool existByUsername(string username);
    void addUser(const User& user) throw(invalid_argument);
    void deleteUser(string username);
    void updateUser(const User& user);
    User getUser(string username);
    vector<User> getAllUsers();

private:
    vector<User>* usersPtr;
};

#endif // USERDAO_H
