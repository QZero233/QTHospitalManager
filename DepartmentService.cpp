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
    //TODO check dependent relationship
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
        if(duty.getDepartmentId()==departmentId)
            result++;
    }

    return result;
}

int DepartmentService::getCapacityById(int departmentId){
    return dutyDao.getCountByDepartmentId(departmentId);
}
