#pragma once
#ifndef DEPARTMENT_SERVICE
#define DEPARTMENT_SERVICE

#include "Department.h"
#include "DataSource.h"
#include <vector>

using namespace std;

class DepartmentService {
private:
	DataSource* dataSourcePtr;

public:
	DepartmentService();

    void checkDepartmentData(const Department& department) throw(invalid_argument);

    void addDepartment(const Department& department) throw(invalid_argument);
    void deleteDepartment(int id) throw(runtime_error);
    void updateDepartment(const Department& department) throw(invalid_argument,runtime_error);
	Department getDepartment(int id);

    vector<Department> getAllDepartments();
};


#endif
