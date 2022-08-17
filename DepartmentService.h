#pragma once
#ifndef DEPARTMENT_SERVICE
#define DEPARTMENT_SERVICE

#include "DepartmentDao.h"
#include "AppointmentDao.h"
#include <vector>

using namespace std;

class DepartmentService {
private:
    DepartmentDao dao;
    AppointmentDao appointmentDao;

public:
	DepartmentService();

    void checkDepartmentData(const Department& department) throw(invalid_argument);

    void addDepartment(const Department& department) throw(invalid_argument);
    void deleteDepartment(int id) throw(runtime_error);
    void updateDepartment(const Department& department) throw(invalid_argument,runtime_error);
	Department getDepartment(int id);

    int getAppointmentCountById(int departmentId);

    vector<Department> getAllDepartments();
};


#endif
