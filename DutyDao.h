#ifndef DUTYDAO_H
#define DUTYDAO_H


#include "DataSource.h"

class DutyDao
{
public:
    DutyDao(){
        DataSource* dataSourcePtr=DataSource::getInstance();
        dutiesPtr=dataSourcePtr->getDutiesPtr();
    }

    int getIndexById(int id) throw(runtime_error);
    bool existById(int id);
    void addDuty(const Duty& duty) throw(invalid_argument);
    void deleteDuty(int id);
    void updateDuty(const Duty& duty);
    Duty getDuty(int id);
    vector<Duty> getAllDuties();

    int getCountByDepartmentId(int departmentId);

    vector<Duty> getAllByDepartmentId(int departmentId);
private:
    vector<Duty>* dutiesPtr;
};


#endif // DUTYDAO_H
