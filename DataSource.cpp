#include "DataSource.h"

#include <stdexcept>
#include <fstream>

using namespace std;

DataSource* DataSource::instance = NULL;

DataSource* DataSource::getInstance() {
	if (instance == NULL)
		instance = new DataSource;
	return instance;
}

void DataSource::setStorageFilePath(const string& fileName) {
	storageFileName = fileName;
}

void DataSource::loadFromFile() {
    //fstream fs(storageFileName,ios::in);
    //Departments first
    /*
     * int id;
    string name;
    int idOfDutyDoctor;
    long appointmentStartTime=-1;
    long appointmentEndTime=-1;
    int capacity;
    string address;
    string telephone;
    */
    departments.clear();
    appointments.clear();
    /*while(true){
        int id;
        fs>>id;
        if(id==-1)
            break;

        string name;
        int idOfDutyDoctor;
        long appointmentStartTime=-1;
        long appointmentEndTime=-1;
        int capacity;
        string address;
        string telephone;

        fs>>name>>idOfDutyDoctor>>appointmentStartTime>>appointmentEndTime>>capacity>>address>>telephone;

        departments.push_back(Department(id,name,idOfDutyDoctor,appointmentStartTime,appointmentEndTime,
                                         capacity,address,telephone));
    }

    while(true){
        int id;
        fs>>id;
        if(id==-1)
            break;

        string name;
        string telephone;
        int gender;
        int age;
        long appointmentTime;
        int departmentId;

        fs>>name>>telephone>>gender>>age>>appointmentTime>>departmentId;

        Appointment appointment;
        appointment.setId(id);
        appointment.setName(name);
        appointment.setTelephone(telephone);
        appointment.setAge(age);
        appointment.setGender(gender);
        appointment.setAppointmentTime(appointmentTime);
        appointment.setDepartmentId(departmentId);

        appointments.push_back(appointment);
    }

    fs.close();*/
}

void DataSource::saveToFile() {
    //Departments first
    /*
     * int id;
    string name;
    int idOfDutyDoctor;
    long appointmentStartTime=-1;
    long appointmentEndTime=-1;
    int capacity;
    string address;
    string telephone;
    */
    /*fstream fs(storageFileName,ios::out);
    for(Department department:departments){
        fs<<department.getId()<<endl
         <<department.getName()<<endl
        <<department.getIdOfDutyDoctor()<<endl
        <<department.getAppointmentStartTime()<<endl
        <<department.getAppointmentEndTime()<<endl
        <<department.getCapacity()<<endl
        <<department.getAddress()<<endl
        <<department.getTelephone()<<endl;
    }
    fs<<-1<<endl;*/

    //Then appointments
    /*
     * int id;
    string name;
    string telephone;
    int gender;
    int age;
    long appointmentTime;
    int departmentId;
    */
    /*for(Appointment appointment:appointments){
        fs<<appointment.getId()<<endl
         <<appointment.getName()<<endl
        <<appointment.getTelephone()<<endl
        <<appointment.getGender()<<endl
        <<appointment.getAge()<<endl
        <<appointment.getAppointmentTime()<<endl
        <<appointment.getDepartmentId()<<endl;
    }
    fs<<-1;

    fs.close();*/
}

vector<Department>* DataSource::getDepartmentsPtr(){
    return &departments;
}

vector<Appointment>* DataSource::getAppointmentsPtr(){
    return &appointments;
}
