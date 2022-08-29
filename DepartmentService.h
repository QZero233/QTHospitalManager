#pragma once
#ifndef DEPARTMENT_SERVICE
#define DEPARTMENT_SERVICE

#include "DepartmentDao.h"
#include "AppointmentDao.h"
#include "DutyDao.h"
#include "DoctorDao.h"
#include <vector>

using namespace std;

class DepartmentService {
private:
    DepartmentDao dao;
    AppointmentDao appointmentDao;
    DutyDao dutyDao;
    DoctorDao doctorDao;

public:
	DepartmentService();

    void checkDepartmentData(const Department& department) throw(invalid_argument);

    void addDepartment(const Department& department) throw(invalid_argument);
    void deleteDepartment(int id) throw(runtime_error);
    void updateDepartment(const Department& department) throw(invalid_argument,runtime_error);
	Department getDepartment(int id);

    int getAppointmentCountById(int departmentId);
    int getCapacityById(int departmentId);

    int getCapacityByIdAndDateAfter(int departmentId,QDate date);
    int getAppointmentCountByIdAndDateAfter(int departmentId,QDate date);

    int getCapacityByIdAndDate(int departmentId,QDate date);
    int getAppointmentCountByIdAndDate(int departmentId,QDate date);

    vector<Department> getAllDepartments();
};


#endif
