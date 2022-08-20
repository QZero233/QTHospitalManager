#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>

using namespace std;

class Doctor
{
public:
    //高级
    static const int POSITION_SENIOR=0;
    //初级
    static const int POSITION_JUNIOR=1;
    //实习
    static const int POSITION_PRACTICE=2;

    Doctor():
        id(-1),
        name(""),
        position(-1){}

    Doctor(int id,string name,int position):
        id(id),
        name(name),
        position(position){}

    void setId(int id){
        this->id=id;
    }

    int getId() const{
        return id;
    }

    void setName(string name){
        this->name=name;
    }

    string getName() const{
        return name;
    }

    void setPosition(int position){
        this->position=position;
    }

    int getPosition() const{
        return position;
    }
private:
    int id;
    string name;
    int position;


};

#endif // DOCTOR_H
