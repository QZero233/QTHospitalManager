
#include "DutyService.h"

#include <stdexcept>

using namespace std;

DutyService::DutyService() {

}

void DutyService::checkDutyDataMembers(const Duty& duty) throw(invalid_argument){
    if(!doctorDao.existById(duty.getDoctorId()))
        throw invalid_argument("不存在ID为 "+to_string(duty.getDoctorId())+" 的医生");
}

void DutyService::addDuty(const Duty& duty) throw(invalid_argument) {
    checkDutyDataMembers(duty);

    vector<Duty> duties=dao.getAllDuties();
    for(Duty data:duties){
        if(data.getDoctorId()!=duty.getDoctorId())
            continue;

        if(data.getDutyDate()==duty.getDutyDate() && data.getDutyTimePeriod()==duty.getDutyTimePeriod())
            throw invalid_argument("该医生在该时段已排班，无法添加");
    }

    dao.addDuty(duty);
}

void DutyService::deleteDuty(int id) throw(runtime_error) {
    //Check appointment
    vector<Appointment> appointments=appointmentDao.getAllAppointments();
    for(Appointment appointment:appointments){
        if(appointment.getDutyId()==id)
            throw runtime_error("该排班已被预约，无法删除，请先删除预约记录");
    }
    dao.deleteDuty(id);
}

void DutyService::updateDuty(const Duty& duty) throw(invalid_argument,runtime_error){
    checkDutyDataMembers(duty);
    dao.updateDuty(duty);
}

Duty DutyService::getDuty(int id) {
    return dao.getDuty(id);
}

vector<Duty> DutyService::getAllDuties(){
    return dao.getAllDuties();
}

vector<Duty> DutyService::getAllByDepartmentId(int departmentId){
    vector<Duty> result;
    vector<Duty> duties=dao.getAllDuties();

    for(Duty duty:duties){
        Doctor doctor=doctorDao.getDoctor(duty.getDoctorId());
        if(doctor.getDepartmentId()==departmentId)
            result.push_back(duty);
    }

    return result;
}

int DutyService::getUniqueId(){
    int id=0;
    vector<Duty> duties=dao.getAllDuties();

    for(Duty duty:duties){
        if(duty.getId()>id)
            id=duty.getId();
    }

    return id+1;
}

int DutyService::getCapacityById(int id){
    int result=0;
    vector<Duty> duties=dao.getAllDuties();
    for(Duty duty:duties){
        if(duty.getId()==id){
            result+=duty.getCapacityEachPeriod()*
                    Appointment::getTimePeriodsByDutyTimePeriod(duty.getDutyTimePeriod()).size();
        }
    }

    return result;
}


