#pragma once

#ifndef APPOINTMENT_SERVICE_H
#define APPOINTMENT_SERVICE_H

#include "AppointmentDao.h"
#include "DepartmentDao.h"
#include "DutyDao.h"
#include <vector>

using namespace std;

class AppointmentService{
private:
    AppointmentDao dao;
    DepartmentDao departmentDao;
    DutyDao dutyDao;

public:
	AppointmentService();

    void checkAppointmentData(const Appointment& appointment) throw(invalid_argument);

    void addAppointment(const Appointment& appointment) throw(invalid_argument,runtime_error);
    void deleteAppointment(int appointmentId);
    Appointment getAppointment(int appointmentId);

    bool existByDutyId(int dutyId);

    vector<Appointment> getAllAppointmentsByDepartmentId(int departmentId);
    vector<Appointment> getAllAppointmentsByTelephone(string telephone);
    vector<Appointment> getAllAppointments();

    vector<Appointment> getAllAppointmentsByNameAndTelephone(string name,string telephone);

    int getUniqueId();
};

#endif

