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

	void addDepartment(const Department& department);
	void deleteDepartment(int id);
	void updateDepartment(const Department& department);
	Department getDepartment(int id);

    vector<Department> getAllDepartments();
};


#endif
