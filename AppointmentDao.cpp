#include "AppointmentDao.h"

int AppointmentDao::getIndexById(int id) throw(runtime_error){
    for (int i = 0; i < appointmentsPtr->size(); i++) {
        if (appointmentsPtr->at(i).getId() == id)
            return i;
    }

    throw runtime_error("不能找到ID为"+to_string(id)+"的预约");
}

bool AppointmentDao::existById(int id){
    try {
        getIndexById(id);
        return true;
    }
    catch (runtime_error& e) {
        return false;
    }
}

void AppointmentDao::addAppointment(const Appointment& appointment) throw(invalid_argument){
    if (existById(appointment.getId())) {
        throw invalid_argument("ID为"+to_string(appointment.getId())+"的预约已存在，无法添加");
    }

    appointmentsPtr->push_back(appointment);
}

void AppointmentDao::deleteAppointment(int id){
    int index = getIndexById(id);

    vector<Appointment> backup = *appointmentsPtr;
    *appointmentsPtr = vector<Appointment>();
    for (int i = 0; i < backup.size(); i++) {
        if (i != index)
            appointmentsPtr->push_back(backup[i]);
    }
}

void AppointmentDao::updateAppointment(const Appointment& appointment){
    int index = getIndexById(appointment.getId());
    (*appointmentsPtr)[index]=appointment;
}

Appointment AppointmentDao::getAppointment(int id){
    int index = getIndexById(id);
    return appointmentsPtr->at(index);
}

vector<Appointment> AppointmentDao::getAllAppointments(){
    return *appointmentsPtr;
}

bool AppointmentDao::existByDutyId(int dutyId){
    for(int i=0;i<appointmentsPtr->size();i++){
        if(appointmentsPtr->at(i).getDutyId()==dutyId)
            return true;
    }

    return false;
}

