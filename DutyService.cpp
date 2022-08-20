
#include "DutyService.h"

#include <stdexcept>

using namespace std;

DutyService::DutyService() {

}

void DutyService::checkDutyDataMembers(const Duty& duty) throw(invalid_argument){
    if(!departmentDao.existById(duty.getDepartmentId()))
        throw invalid_argument("不存在ID为 "+to_string(duty.getDepartmentId())+" 的门诊部门");
    if(!doctorDao.existById(duty.getDoctorId()))
        throw invalid_argument("不存在ID为 "+to_string(duty.getDoctorId())+" 的医生");

    //TODO check if the doctor is busy(has another duty) at that time
}

void DutyService::addDuty(const Duty& duty) throw(invalid_argument) {
    checkDutyDataMembers(duty);
    dao.addDuty(duty);
}

void DutyService::deleteDuty(int id) throw(runtime_error) {
    //TODO check dependent relationship
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
    return dao.getAllByDepartmentId(departmentId);
}


