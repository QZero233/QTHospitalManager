#include "DoctorService.h"

#include <stdexcept>

using namespace std;

DoctorService::DoctorService() {

}

void DoctorService::addDoctor(const Doctor& doctor) throw(invalid_argument) {
    dao.addDoctor(doctor);
}

void DoctorService::deleteDoctor(int id) throw(runtime_error) {
    //TODO check dependent relationship
    dao.deleteDoctor(id);
}

void DoctorService::updateDoctor(const Doctor& doctor) throw(invalid_argument,runtime_error){
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
