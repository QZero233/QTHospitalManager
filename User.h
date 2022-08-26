#ifndef USER_H
#define USER_H

#include <string>

#include <QDate>

using namespace std;

class User
{
public:
    User():
    username(""),
    password(""),
    group(-1),
    name(""),
    telephone(""),
    gender(-1),
    birthDate(-1){

    }

    User(string username,string password,int group,string name,string telephone,int gender,long long birthDate):
        username(username),
        password(password),
        group(group),
        name(name),
        telephone(telephone),
        gender(gender),
        birthDate(birthDate)
        {

    }

    static const int GENDER_FEMALE = 0;
    static const int GENDER_MALE = 1;

    static const int GROUP_PATIENT=0;
    static const int GROUP_ADMIN=1;

    void setUsername(string username){
        this->username=username;
    }

    string getUsername() const{
        return username;
    }

    void setPassword(string password){
        this->password=password;
    }

    string getPassword() const{
        return password;
    }

    void setGroup(int group){
        this->group=group;
    }

    int getGroup() const{
        return group;
    }

    void setName(string name){
        this->name=name;
    }

    string getName() const{
        return name;
    }

    void setTelephone(string telephone){
        this->telephone=telephone;
    }

    string getTelephone() const{
        return telephone;
    }

    void setGender(int gender){
        this->gender=gender;
    }

    int getGender() const{
        return gender;
    }

    void setBirthDate(long long birthDate){
        this->birthDate=birthDate;
    }

    long long getBirthDate() const{
        return birthDate;
    }

    int getAge() const{
        QDate current=QDate::currentDate();
        QDate birth=QDate::fromJulianDay(birthDate);

        int yearDelta=current.year()-birth.year()-1;
        birth.setDate(current.year(),birth.month(),birth.day());
        if(current>=birth){
            yearDelta++;
        }

        return yearDelta;
    }
private:
    string username;
    string password;
    int group;

    string name;
    string telephone;
    int gender;
    long long birthDate;
};

#endif // USER_H
