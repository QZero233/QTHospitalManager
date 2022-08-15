#include "AppointmentService.h"
#include <stdexcept>
#include <QDateTime>

using namespace std;

AppointmentService::AppointmentService() {
	dataSourcePtr = DataSource::getInstance();
}

int AppointmentService::getIndexById(int departmentId, int appointmentId) {
	Department department = dataSourcePtr->getDepartment(departmentId);
	vector<Appointment>* appointmentsPtr = department.getAppointmentsPtr();
	for (int i = 0; i < appointmentsPtr->size(); i++) {
		if (appointmentsPtr->at(i).getId() == appointmentId)
			return i;
	}

	throw runtime_error("No appointment with id " + to_string(appointmentId) + " in department " + department.getName());
}

bool AppointmentService::existById(int departmentId, int appointmentId) {
	try {
		getIndexById(departmentId, appointmentId);
		return true;
	}
	catch (runtime_error& e) {
		return false;
	}
}

void AppointmentService::addAppointment(int departmentId, const Appointment& appointment) {
	Department department = dataSourcePtr->getDepartment(departmentId);
	if (existById(departmentId, appointment.getId())){
		throw invalid_argument("Appointment with id " + to_string(appointment.getId()) + " already exists");
	}

	if (department.getAppointmentsPtr()->size() >= department.getCapacity()) {
		throw runtime_error("Appointment number exceeds capacity");
	}

    long time=QDateTime::fromSecsSinceEpoch(appointment.getAppointmentTime()).time().msecsSinceStartOfDay();
    if(time<department.getAppointmentStartTime() || time>department.getAppointmentEndTime()){
        throw runtime_error("预约时间不在接诊时间范围内");
    }

	department.getAppointmentsPtr()->push_back(appointment);
	dataSourcePtr->updateDepartment(department);
}

void AppointmentService::deleteAppointment(int departmentId, int appointmentId) {
	Department department = dataSourcePtr->getDepartment(departmentId);
	int index = getIndexById(departmentId, appointmentId);
	
	vector<Appointment>* appointmentsPtr = department.getAppointmentsPtr();
	vector<Appointment> newAppointments;
	for (int i = 0; i < appointmentsPtr->size(); i++) {
		if (i != index)
			newAppointments.push_back(appointmentsPtr->at(i));
	}

	department.setAppointments(newAppointments);
	dataSourcePtr->updateDepartment(department);
}

void AppointmentService::updateAppointment(int departmentId, const Appointment& appointment){
	Department department = dataSourcePtr->getDepartment(departmentId);
	int index = getIndexById(departmentId, appointment.getId());

    long time=QDateTime::fromSecsSinceEpoch(appointment.getAppointmentTime()).time().msecsSinceStartOfDay();
    if(time<department.getAppointmentStartTime() || time>department.getAppointmentEndTime()){
        throw runtime_error("预约时间不在接诊时间范围内");
    }

	vector<Appointment>* appointmentsPtr = department.getAppointmentsPtr();
	(*appointmentsPtr)[index] = appointment;

	dataSourcePtr->updateDepartment(department);
}

Appointment AppointmentService::getAppointment(int departmentId, int appointmentId) {
	Department department = dataSourcePtr->getDepartment(departmentId);
	int index = getIndexById(departmentId, appointmentId);
	return department.getAppointmentsPtr()->at(index);
}

vector<Appointment> AppointmentService::getAllAppointments(int departmentId){
    Department department = dataSourcePtr->getDepartment(departmentId);
    return department.getAppointments();
}
