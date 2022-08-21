#ifndef DUTYSERVICE_H
#define DUTYSERVICE_H

#include "DepartmentDao.h"
#include "DoctorDao.h"
#include "DutyDao.h"
#include "AppointmentDao.h"

using namespace std;

class DutyService {
private:
    DutyDao dao;
    DepartmentDao departmentDao;
    DutyDao dutyDao;
    DoctorDao doctorDao;
    AppointmentDao appointmentDao;

public:
    DutyService();

    void checkDutyDataMembers(const Duty& duty) throw(invalid_argument);

    void addDuty(const Duty& duty) throw(invalid_argument);
    void deleteDuty(int id) throw(runtime_error);
    void updateDuty(const Duty& duty) throw(invalid_argument,runtime_error);
    Duty getDuty(int id);

    vector<Duty> getAllDuties();

    vector<Duty> getAllByDepartmentId(int departmentId);

    int getUniqueId();
};

#endif // DUTYSERVICE_H
