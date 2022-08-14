#pragma once

#ifndef APPOINTMENT_SERVICE_H
#define APPOINTMENT_SERVICE_H

#include "DataSource.h"
#include "Appointment.h"
#include "Department.h"
#include <vector>

using namespace std;

class AppointmentService{
private:
	DataSource* dataSourcePtr;

public:
	AppointmentService();

	int getIndexById(int departmentId, int appointmentId);
	bool existById(int departmentId, int appointmentId);

	void addAppointment(int departmentId,const Appointment& appointment);
	void deleteAppointment(int departmentId, int appointmentId);
	void updateAppointment(int departmentId, const Appointment& appointment);
	Appointment getAppointment(int departmentId, int appointmentId);

    vector<Appointment> getAllAppointments(int departmentId);
};

#endif

