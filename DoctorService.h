#ifndef DOCTORSERVICE_H
#define DOCTORSERVICE_H

#include "DoctorDao.h"
#include "DutyDao.h"
#include "DepartmentDao.h"

using namespace std;

class DoctorService {
private:
    DoctorDao dao;
    DepartmentDao departmentDao;
    DutyDao dutyDao;

public:
    DoctorService();

    void checkDoctorDataArguments(const Doctor& doctor) throw(invalid_argument);

    void addDoctor(const Doctor& doctor) throw(invalid_argument);
    void deleteDoctor(int id) throw(runtime_error);
    void updateDoctor(const Doctor& doctor) throw(invalid_argument,runtime_error);
    Doctor getDoctor(int id);

    vector<Doctor> getAllDoctors();

    bool existByDepartmentId(int departmentId);

    int getUniqueId();
};

#endif // DOCTORSERVICE_H
