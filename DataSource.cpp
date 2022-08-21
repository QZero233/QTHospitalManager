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
    fstream fs(storageFileName,ios::in);
    //Departments first
    /*
     * int id;
    string name;
    string address;
    string telephone;
    */
    departments.clear();
    appointments.clear();
    doctors.clear();
    duties.clear();

    while(true){
        int id;
        fs>>id;
        if(id==-1)
            break;

        string name;
        string address;
        string telephone;

        fs>>name>>address>>telephone;

        departments.push_back(Department(id,name,address,telephone));
    }

    /*
     * int id;
    string name;
    string telephone;
    int gender;
    int age;
    int dutyId;
    */
    while(true){
        int id;
        fs>>id;
        if(id==-1)
            break;

        string name;
        string telephone;
        int gender;
        int age;
        int dutyId;

        fs>>name>>telephone>>gender>>age>>dutyId;

        Appointment appointment;
        appointment.setId(id);
        appointment.setName(name);
        appointment.setTelephone(telephone);
        appointment.setAge(age);
        appointment.setGender(gender);
        appointment.setDutyId(dutyId);

        appointments.push_back(appointment);
    }

    //Then doctors
    /*
     * int id;
    string name;
    int position;
    int departmentId;
     */
    while(true){
        int id;
        fs>>id;
        if(id==-1)
            break;

        string name;
        int position;
        int departmentId;

        fs>>name>>position>>departmentId;

        doctors.push_back(Doctor(id,name,position,departmentId));
    }

    //The duties
    /*
     * int id;
    int doctorId;
    int dutyTime;
    long long dutyDate;
     */
    while(true){
        int id;
        fs>>id;
        if(id==-1)
            break;

        int doctorId;
        int dutyTime;
        long long dutyDate;

        fs>>doctorId>>dutyTime>>dutyDate;

        duties.push_back(Duty(id,doctorId,dutyTime,dutyDate));
    }

    fs.close();
}

void DataSource::saveToFile() {
    //Departments first
    /*
     * int id;
    string name;
    string address;
    string telephone;
    */
    fstream fs(storageFileName,ios::out);
    for(Department department:departments){
        fs<<department.getId()<<endl
         <<department.getName()<<endl
        <<department.getAddress()<<endl
        <<department.getTelephone()<<endl;
    }
    fs<<-1<<endl;

    //Then appointments
    /*
     * int id;
    string name;
    string telephone;
    int gender;
    int age;
    int dutyId;
    */
    for(Appointment appointment:appointments){
        fs<<appointment.getId()<<endl
         <<appointment.getName()<<endl
        <<appointment.getTelephone()<<endl
        <<appointment.getGender()<<endl
        <<appointment.getAge()<<endl
        <<appointment.getDutyId()<<endl;
    }
    fs<<-1<<endl;

    //Then doctors
    /*
     * int id;
    string name;
    int position;
    int departmentId;
     */
    for(Doctor doctor:doctors){
        fs<<doctor.getId()<<endl
         <<doctor.getName()<<endl
        <<doctor.getPosition()<<endl
        <<doctor.getDepartmentId()<<endl;
    }
    fs<<-1<<endl;

    //The duties
    /*
     * int id;
    int doctorId;
    int dutyTime;
    long long dutyDate;
     */
    for(Duty duty:duties){
        fs<<duty.getId()<<endl
         <<duty.getDoctorId()<<endl
        <<duty.getDutyTime()<<endl
        <<duty.getDutyDate()<<endl;
    }
    fs<<-1<<endl;

    fs.close();
}

vector<Department>* DataSource::getDepartmentsPtr(){
    return &departments;
}

vector<Appointment>* DataSource::getAppointmentsPtr(){
    return &appointments;
}
