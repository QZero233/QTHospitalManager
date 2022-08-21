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
}


void AppointmentService::addAppointment(const Appointment& appointment)
throw(invalid_argument,runtime_error){
    checkAppointmentData(appointment);
    //Check id uniqueness
    if (dao.existById(appointment.getId())){
        throw invalid_argument("已经有ID为" + to_string(appointment.getId()) + "的预约信息存在");
	}

    //Check if the duty is reserved
    if(dao.existByDutyId(appointment.getDutyId())){
        throw runtime_error("无法添加预约，该时段该医生已被预约");
    }

    dao.addAppointment(appointment);
}

void AppointmentService::deleteAppointment(int appointmentId) {
    dao.deleteAppointment(appointmentId);
}

Appointment AppointmentService::getAppointment(int appointmentId) {
    dao.getAppointment(appointmentId);
}

vector<Appointment> AppointmentService::getAllAppointments(){
    return dao.getAllAppointments();
}

vector<Appointment> AppointmentService::getAllAppointmentsByTelephone(string telephone){
    return dao.getAllAppointmentsByTelephone(telephone);
}

vector<Appointment> AppointmentService::getAllAppointmentsByDepartmentId(int departmentId){
    vector<Appointment> appointments=dao.getAllAppointments();
    vector<Appointment> result;
    for(int i=0;i<appointments.size();i++){
        int doctorId=dutyDao.getDuty(appointments[i].getDutyId()).getDoctorId();
        Doctor doctor=doctorDao.getDoctor(doctorId);
        if(doctor.getDepartmentId()==departmentId){
            result.push_back(appointments[i]);
        }
    }

    return result;
}

bool AppointmentService::existByDutyId(int dutyId){
   return dao.existByDutyId(dutyId);
}

vector<Appointment> AppointmentService::getAllAppointmentsByNameAndTelephone(string name,string telephone){
    return dao.getAllAppointmentsByNameAndTelephone(name,telephone);
}

int AppointmentService::getUniqueId(){
    int biggestId=0;
    vector<Appointment> appointments=dao.getAllAppointments();
    for(int i=0;i<appointments.size();i++){
        if(appointments[i].getId()>biggestId)
            biggestId=appointments[i].getId();
    }
    return biggestId+1;
}
