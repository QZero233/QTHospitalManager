#pragma once

#ifndef APPOINTMENT_SERVICE_H
#define APPOINTMENT_SERVICE_H

#include "AppointmentDao.h"
#include "DepartmentDao.h"
#include <vector>

using namespace std;

class AppointmentService{
private:
    AppointmentDao dao;
    DepartmentDao departmentDao;


public:
	AppointmentService();

    void checkAppointmentData(const Appointment& appointment) throw(invalid_argument);

    void addAppointment(const Appointment& appointment) throw(invalid_argument,runtime_error);
    void deleteAppointment(int appointmentId);
    void updateAppointment(const Appointment& appointment) throw(invalid_argument);
    Appointment getAppointment(int appointmentId);

    vector<Appointment> getAllAppointmentsByDepartmentId(int departmentId);
    vector<Appointment> getAllAppointmentsByTelephone(string telephone);
    vector<Appointment> getAllAppointments();

    Department getBelongingDepartment(const Appointment& appointment);
};

#endif

