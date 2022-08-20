#ifndef DOCTORDAO_H
#define DOCTORDAO_H


#include "DataSource.h"

class DoctorDao
{
public:
    DoctorDao(){
        DataSource* dataSourcePtr=DataSource::getInstance();
        doctorsPtr=dataSourcePtr->getDoctorsPtr();
    }

    int getIndexById(int id) throw(runtime_error);
    bool existById(int id);
    void addDoctor(const Doctor& doctor) throw(invalid_argument);
    void deleteDoctor(int id);
    void updateDoctor(const Doctor& doctor);
    Doctor getDoctor(int id);
    vector<Doctor> getAllDoctors();

private:
    vector<Doctor>* doctorsPtr;
};

#endif // DOCTORDAO_H
