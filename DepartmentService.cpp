#include "DepartmentService.h"

#include <QDateTime>
#include <stdexcept>

using namespace std;

DepartmentService::DepartmentService() {

}

void DepartmentService::checkDepartmentData(const Department& department) throw(invalid_argument){

}

void DepartmentService::addDepartment(const Department& department) throw(invalid_argument) {
    checkDepartmentData(department);
    dao.addDepartment(department);
}

void DepartmentService::deleteDepartment(int id) throw(runtime_error) {
    //Check doctor
    vector<Doctor> doctors=doctorDao.getAllDoctors();
    for(Doctor doctor:doctors){
        if(doctor.getDepartmentId()==id)
            throw runtime_error("该科室存在医生记录，无法删除，请先删除所有医生记录");
    }
    dao.deleteDepartment(id);
}

void DepartmentService::updateDepartment(const Department& department) throw(invalid_argument,runtime_error){
    checkDepartmentData(department);
    dao.updateDepartment(department);
}

Department DepartmentService::getDepartment(int id) {
    return dao.getDepartment(id);
}

vector<Department> DepartmentService::getAllDepartments(){
    return dao.getAllDepartments();
}

int DepartmentService::getAppointmentCountById(int departmentId){
    int result=0;

    vector<Appointment> appoinemtnes=appointmentDao.getAllAppointments();
    for(Appointment appointment:appoinemtnes){
        Duty duty=dutyDao.getDuty(appointment.getDutyId());
        Doctor doctor=doctorDao.getDoctor(duty.getDoctorId());
        if(doctor.getDepartmentId()==departmentId)
            result++;
    }

    return result;
}

int DepartmentService::getCapacityById(int departmentId){
    int result=0;
    vector<Duty> duties=dutyDao.getAllDuties();
    for(Duty duty:duties){
        Doctor doctor=doctorDao.getDoctor(duty.getDoctorId());
        if(doctor.getDepartmentId()==departmentId)
            result++;
    }
    return result;
}
