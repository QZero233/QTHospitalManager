#include "AppointmentService.h"
#include <stdexcept>
#include <QDateTime>

using namespace std;

AppointmentService::AppointmentService() {

}

void AppointmentService::checkAppointmentData(const Appointment& appointment) throw(invalid_argument){
    if (appointment.getGender() != Appointment::GENDER_MALE &&
            appointment.getGender() != Appointment::GENDER_FEMALE) {
        throw invalid_argument("Gender must be 0 or 1");
    }

    if (appointment.getAge() <= 0) {
        throw invalid_argument("Age must be greater than 0");
    }

    if (appointment.getAppointmentTime() <= 0) {
        throw invalid_argument("Time must be greater than 0");
    }

    //Check time suitability
    Department department = departmentDao.getDepartment(appointment.getDepartmentId());
    long time=QDateTime::fromSecsSinceEpoch(appointment.getAppointmentTime()).time().msecsSinceStartOfDay();
    if(time<department.getAppointmentStartTime() || time>department.getAppointmentEndTime()){
        throw invalid_argument("预约时间不在接诊时间范围内");
    }
}


void AppointmentService::addAppointment(const Appointment& appointment)
throw(invalid_argument,runtime_error){
    checkAppointmentData(appointment);
    //Check id uniqueness
    if (dao.existById(appointment.getId())){
		throw invalid_argument("Appointment with id " + to_string(appointment.getId()) + " already exists");
	}

    //Check capacity
    Department department = departmentDao.getDepartment(appointment.getDepartmentId());
    int appointmentCount=dao.getCountByDepartmentId(appointment.getDepartmentId());
    if (appointmentCount >= department.getCapacity()) {
        throw runtime_error("Appointment number exceeds capacity");
    }

    dao.addAppointment(appointment);
}

void AppointmentService::deleteAppointment(int appointmentId) {
    dao.deleteAppointment(appointmentId);
}

void AppointmentService::updateAppointment(const Appointment& appointment)
throw(invalid_argument){
    checkAppointmentData(appointment);
    dao.updateAppointment(appointment);
}

Appointment AppointmentService::getAppointment(int appointmentId) {
    dao.getAppointment(appointmentId);
}

vector<Appointment> AppointmentService::getAllAppointments(){
    return dao.getAllAppointments();
}

vector<Appointment> AppointmentService::getAllAppointmentsByDepartmentId(int departmentId){
    return dao.getAllByDepartmentId(departmentId);
}

Department AppointmentService::getBelongingDepartment(const Appointment& appointment){
    return departmentDao.getDepartment(appointment.getDepartmentId());
}

vector<Appointment> AppointmentService::getAllAppointmentsByTelephone(string telephone){
    return dao.getAllAppointmentsByTelephone(telephone);
}
