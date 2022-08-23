#include "UserService.h"

#include <QDateTime>
#include <stdexcept>

#include "Appointment.h"

using namespace std;

UserService::UserService() {

}

void UserService::checkUserData(const User& user) throw(invalid_argument){
    if (user.getGender() != User::GENDER_MALE &&
            user.getGender() != User::GENDER_FEMALE) {
        throw invalid_argument("Gender must be 0 or 1");
    }

    if (user.getAge() <= 0) {
        throw invalid_argument("Age must be greater than 0");
    }
}

void UserService::addUser(const User& user) throw(invalid_argument) {
    checkUserData(user);
    dao.addUser(user);
}

void UserService::deleteUser(string username) throw(runtime_error) {
    vector<Appointment> appointments=appointmentDao.getAllAppointments();
    for(Appointment appointment:appointments){
        if(appointment.getUsername()==username)
            throw runtime_error("该用户存在预约，无法删除");
    }

    dao.deleteUser(username);
}

void UserService::updateUser(const User& user) throw(invalid_argument,runtime_error){
    checkUserData(user);
    dao.updateUser(user);
}

User UserService::getUser(string username) {
    return dao.getUser(username);
}

vector<User> UserService::getAllUsers(){
    return dao.getAllUsers();
}

bool UserService::existByUsernameAndPassword(string username,string password){
    vector<User> users=dao.getAllUsers();
    for(User user:users){
        if(user.getUsername()==username && user.getPassword()==password)
            return true;
    }

    return false;
}

User UserService::getByUsernameAndPassword(string username,string password){
    vector<User> users=dao.getAllUsers();
    for(User user:users){
        if(user.getUsername()==username && user.getPassword()==password)
            return user;
    }

    throw runtime_error("不存在符合条件的用户");
}
