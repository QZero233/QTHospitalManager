
#include "Department.h"
#include "Appointment.h"

#include "DepartmentService.h"
#include "AppointmentService.h"

#include "DataSource.h"

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

int main() {
	DataSource* dataSourcePtr = DataSource::getInstance();
	dataSourcePtr->setStorageFilePath("record.data");
	dataSourcePtr->loadFromFile();

	DepartmentService departmentService;
	AppointmentService appointmentService;

	//Generate test data
	Department department1(1,"���ȿ�",996,time(0),time(0)+5*60*60*1000,10,"УҽԺ","88888888");
	Department department2(5,"������",888,time(0),time(0)+5*60*60*1000,5,"УҽԺ","77777777");
	Department department3(2,"�����",666,time(0),time(0)+5*60*60*1000,30,"УҽԺ","66666666");

	departmentService.addDepartment(department1);
	departmentService.addDepartment(department2);
	departmentService.addDepartment(department3);

	//Test appointment add delete update query
	for (int i = 1; i <= 10; i++) {
		Appointment appointment;
		appointment.setId(i);
		appointment.setName("����"+to_string(i));
		appointment.setTelephone("8848" + to_string(i));
		appointment.setGender(Appointment::GENDER_MALE);
		appointment.setAge(i);
		appointment.setAppointmentTime(time(0));

		appointmentService.addAppointment(1, appointment);
	}

	appointmentService.deleteAppointment(1, 2);

	Appointment appointment = appointmentService.getAppointment(1, 3);

	appointment.setAge(100);
	appointment.setName("����");
	appointmentService.updateAppointment(1, appointment);

	//


	return 0;
}