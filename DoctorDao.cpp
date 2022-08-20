#include "DoctorDao.h"

int DoctorDao::getIndexById(int id) throw(runtime_error) {
    for (int i = 0; i < doctorsPtr->size(); i++) {
        if (doctorsPtr->at(i).getId() == id)
            return i;
    }

    throw runtime_error("不能找到ID为"+to_string(id)+"的医生");
}

bool DoctorDao::existById(int id) {
    try {
        getIndexById(id);
        return true;
    }
    catch (runtime_error& e) {
        return false;
    }
}

void DoctorDao::addDoctor(const Doctor& doctor) throw(invalid_argument) {
    if (existById(doctor.getId())) {
        throw invalid_argument("ID为"+to_string(doctor.getId())+"的医生部门已存在，无法添加");
    }

    doctorsPtr->push_back(doctor);
}

void DoctorDao::deleteDoctor(int id) {
    int index = getIndexById(id);

    vector<Doctor> backup = *doctorsPtr;
    *doctorsPtr = vector<Doctor>();
    for (int i = 0; i < backup.size(); i++) {
        if (i != index)
            doctorsPtr->push_back(backup[i]);
    }
}

void DoctorDao::updateDoctor(const Doctor& doctor) {
    int index = getIndexById(doctor.getId());
    (*doctorsPtr)[index]=doctor;
}

Doctor DoctorDao::getDoctor(int id) {
    int index = getIndexById(id);
    return doctorsPtr->at(index);
}

vector<Doctor> DoctorDao::getAllDoctors(){
    return *doctorsPtr;
}
