#ifndef DOCTORSERVICE_H
#define DOCTORSERVICE_H

#include "DoctorDao.h"

using namespace std;

class DoctorService {
private:
    DoctorDao dao;

public:
    DoctorService();

    void addDoctor(const Doctor& doctor) throw(invalid_argument);
    void deleteDoctor(int id) throw(runtime_error);
    void updateDoctor(const Doctor& doctor) throw(invalid_argument,runtime_error);
    Doctor getDoctor(int id);

    vector<Doctor> getAllDoctors();

    int getUniqueId();
};

#endif // DOCTORSERVICE_H
