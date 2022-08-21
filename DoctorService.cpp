#include "DoctorService.h"

#include <stdexcept>

using namespace std;

DoctorService::DoctorService() {

}

void DoctorService::checkDoctorDataArguments(const Doctor& doctor) throw(invalid_argument){
    if(!departmentDao.existById(doctor.getDepartmentId()))
        throw invalid_argument("不存在ID为 "+to_string(doctor.getDepartmentId())+" 的科室");
}

void DoctorService::addDoctor(const Doctor& doctor) throw(invalid_argument) {
    checkDoctorDataArguments(doctor);
    dao.addDoctor(doctor);
}

void DoctorService::deleteDoctor(int id) throw(runtime_error) {
    //Check duty
    vector<Duty> duties=dutyDao.getAllDuties();
    for(Duty duty:duties){
        if(duty.getDoctorId()==id)
            throw runtime_error("该医生名下存在排班，无法删除，请先删除相关排班记录");
    }
    dao.deleteDoctor(id);
}

void DoctorService::updateDoctor(const Doctor& doctor) throw(invalid_argument,runtime_error){
    checkDoctorDataArguments(doctor);
    dao.updateDoctor(doctor);
}

Doctor DoctorService::getDoctor(int id) {
    return dao.getDoctor(id);
}

vector<Doctor> DoctorService::getAllDoctors(){
    return dao.getAllDoctors();
}

int DoctorService::getUniqueId(){
    int id=0;
    vector<Doctor> doctors=dao.getAllDoctors();
    for(Doctor doctor:doctors){
        if(doctor.getId()>id)
            id=doctor.getId();
    }
    return id+1;
}

bool DoctorService::existByDepartmentId(int departmentId){
    vector<Doctor> doctors=dao.getAllDoctors();
    for(Doctor doctor:doctors){
        if(doctor.getDepartmentId()==departmentId)
            return true;
    }
    return false;
}
