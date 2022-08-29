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

int DoctorService::getCapacityByDoctorId(int doctorId){
    vector<Duty> duties=dutyDao.getAllDuties();
    int result=0;

    for(Duty duty:duties){
        if(duty.getDoctorId()==doctorId){
            result+=duty.getCapacityEachPeriod()*
                    Appointment::getTimePeriodsByDutyTimePeriod(duty.getDutyTimePeriod()).size();
        }
    }

    return result;
}

int DoctorService::getCapacityByDoctorIdAndDate(int doctorId,QDate date){
    vector<Duty> duties=dutyDao.getAllDuties();
    int result=0;

    for(Duty duty:duties){
        if(duty.getDoctorId()==doctorId && duty.getDutyDate()==date.toJulianDay()){
            result+=duty.getCapacityEachPeriod()*
                    Appointment::getTimePeriodsByDutyTimePeriod(duty.getDutyTimePeriod()).size();
        }
    }

    return result;
}

int DoctorService::getCapacityByDoctorIdAndDateAfter(int doctorId,QDate date){
    vector<Duty> duties=dutyDao.getAllDuties();
    int result=0;

    for(Duty duty:duties){
        if(duty.getDutyDate()<date.toJulianDay())
            continue;

        if(duty.getDoctorId()==doctorId){
            result+=duty.getCapacityEachPeriod()*
                    Appointment::getTimePeriodsByDutyTimePeriod(duty.getDutyTimePeriod()).size();
        }
    }

    return result;
}

int DoctorService::getAppointmentCountByDoctorId(int doctorId){
    vector<Appointment> appointments=appointmentDao.getAllAppointments();
    int result=0;

    for(Appointment appointment:appointments){
        Duty duty=dutyDao.getDuty(appointment.getDutyId());
        if(duty.getDoctorId()==doctorId)
            result++;

    }

    return result;
}

int DoctorService::getAppointmentCountByDoctorIdAndDate(int doctorId,QDate date){
    vector<Appointment> appointments=appointmentDao.getAllAppointments();
    int result=0;

    for(Appointment appointment:appointments){
        Duty duty=dutyDao.getDuty(appointment.getDutyId());
        if(duty.getDoctorId()==doctorId && duty.getDutyDate()==date.toJulianDay())
            result++;

    }

    return result;
}

int DoctorService::getAppointmentCountByDoctorIdAndDateAfter(int doctorId,QDate date){
    vector<Appointment> appointments=appointmentDao.getAllAppointments();
    int result=0;

    for(Appointment appointment:appointments){
        Duty duty=dutyDao.getDuty(appointment.getDutyId());
        if(duty.getDoctorId()==doctorId && duty.getDutyDate()>=date.toJulianDay())
            result++;

    }

    return result;
}

vector<Doctor> DoctorService::getAllByDepartmentId(int departmentId){
    vector<Doctor> doctors=dao.getAllDoctors();
    vector<Doctor> result;

    for(Doctor doctor:doctors){
        if(doctor.getDepartmentId()==departmentId)
            result.push_back(doctor);
    }

    return result;
}
