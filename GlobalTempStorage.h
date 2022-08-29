#ifndef GLOBALTEMPSTORAGE_H
#define GLOBALTEMPSTORAGE_H

#include "User.h"

class GlobalTempStorage
{
public:
    static GlobalTempStorage* getInstance(){
        if(in==nullptr)
            in=new GlobalTempStorage();
        return in;
    }

    User user;

private:
    static GlobalTempStorage* in;
    GlobalTempStorage(){}
};

#endif // GLOBALTEMPSTORAGE_H
