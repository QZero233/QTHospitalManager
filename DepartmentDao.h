#ifndef DEPARTMENTDAO_H
#define DEPARTMENTDAO_H

#include "DataSource.h"

class DepartmentDao
{
public:
    DepartmentDao(){
        DataSource* dataSourcePtr=DataSource::getInstance();
        departmentsPtr=dataSourcePtr->getDepartmentsPtr();
    }

    int getIndexById(int id) throw(runtime_error);
    bool existById(int id);
    void addDepartment(const Department& department) throw(invalid_argument);
    void deleteDepartment(int id);
    void updateDepartment(const Department& department);
    Department getDepartment(int id);
    vector<Department> getAllDepartments();

private:
    vector<Department>* departmentsPtr;
};

#endif // DEPARTMENTDAO_H
