#ifndef USERSERVICE_H
#define USERSERVICE_H


#include "UserDao.h"
#include "AppointmentDao.h"
#include "DutyDao.h"
#include "DoctorDao.h"
#include <vector>

using namespace std;

class UserService {
private:
    UserDao dao;
    AppointmentDao appointmentDao;
    DutyDao dutyDao;
    DoctorDao doctorDao;

public:
    UserService();

    void checkUserData(const User& user) throw(invalid_argument);

    void addUser(const User& user) throw(invalid_argument);
    void deleteUser(string username) throw(runtime_error);
    void updateUser(const User& user) throw(invalid_argument,runtime_error);
    User getUser(string username);

    vector<User> getAllUsers();

    bool existByUsernameAndPassword(string username,string password);
    User getByUsernameAndPassword(string username,string password);
};

#endif // USERSERVICE_H
