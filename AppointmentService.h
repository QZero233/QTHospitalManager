#pragma once

#ifndef APPOINTMENT_SERVICE_H
#define APPOINTMENT_SERVICE_H

#include "AppointmentDao.h"
#include "DepartmentDao.h"
#include "DutyDao.h"
#include "DoctorDao.h"
#include "UserDao.h"
#include <vector>

using namespace std;

class AppointmentService{
private:
    AppointmentDao dao;
    DepartmentDao departmentDao;
    DutyDao dutyDao;
    DoctorDao doctorDao;
    UserDao userDao;

public:
	AppointmentService();

    void checkAppointmentData(const Appointment& appointment) throw(invalid_argument);

    void addAppointment(const Appointment& appointment) throw(invalid_argument,runtime_error);
    void deleteAppointment(int appointmentId);
    Appointment getAppointment(int appointmentId);

    bool existByDutyId(int dutyId);

    vector<Appointment> getAllAppointmentsByDepartmentId(int departmentId);
    vector<Appointment> getAllAppointments();

    vector<Appointment> getAllAppointmentsByNameAndTelephone(string name,string telephone);
    vector<Appointment> getAllByUsername(string username);

    int getUniqueId();

    int getCountByDutyId(int id);
    int getCountByIdAndTimePeriod(int id,int timePeriod);
};

#endif

