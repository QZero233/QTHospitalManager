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
    users.clear();

    if(!fs){
        //Add default admin
        users.push_back(User("admin","123456",User::GROUP_ADMIN,"DefaultAdmin","123456",
                             User::GENDER_MALE,QDate::currentDate().toJulianDay()));
        return;
    }


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
    string username;
    int dutyId;
    int timePeriod;
    */
    while(true){
        int id;
        fs>>id;
        if(id==-1)
            break;

        string username;
        int dutyId;
        int timePeriod;

        fs>>username>>dutyId>>timePeriod;

        Appointment appointment;
        appointment.setId(id);
        appointment.setUsername(username);
        appointment.setDutyId(dutyId);
        appointment.setTimePeriod(timePeriod);

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
    int dutyTimePeriod;
    long long dutyDate;
    int capacityEachPeriod;
     */
    while(true){
        int id;
        fs>>id;
        if(id==-1)
            break;

        int doctorId;
        int dutyTimePeriod;
        long long dutyDate;
        int capacityEachPeriod;

        fs>>doctorId>>dutyTimePeriod>>dutyDate>>capacityEachPeriod;

        duties.push_back(Duty(id,doctorId,dutyTimePeriod,dutyDate,capacityEachPeriod));
    }

    //User
    /*
     * string username;
    string password;
    int group;

    string name;
    string telephone;
    int gender;
    long long birthDate;
     */

    //Count first
    int count;
    fs>>count;
    for(int i=0;i<count;i++){
        string username;
        string password;
        int group;

        string name;
        string telephone;
        int gender;
        long long birthDate;

        fs>>username;
        fs>>password;
        fs>>group>>name>>telephone>>gender>>birthDate;
        users.push_back(User(username,password,group,name,telephone,gender,birthDate));
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
    string username;
    int dutyId;
    int timePeriod;
    */
    for(Appointment appointment:appointments){
        fs<<appointment.getId()<<endl
         <<appointment.getUsername()<<endl
        <<appointment.getDutyId()<<endl
        <<appointment.getTimePeriod()<<endl;
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
    int dutyTimePeriod;
    long long dutyDate;
    int capacityEachPeriod;
     */
    for(Duty duty:duties){
        fs<<duty.getId()<<endl
         <<duty.getDoctorId()<<endl
        <<duty.getDutyTimePeriod()<<endl
        <<duty.getDutyDate()<<endl
        <<duty.getCapacityEachPeriod()<<endl;
    }
    fs<<-1<<endl;

    //Then users
    /*
     * string username;
    string password;
    int group;

    string name;
    string telephone;
    int gender;
    long long birthDate;
     */
    //Count firsr
    fs<<users.size()<<endl;
    for(User user:users){
        fs<<user.getUsername()<<endl
         <<(user.getPassword()==""?"empty":user.getPassword())<<endl
        <<user.getGroup()<<endl
        <<user.getName()<<endl
        <<user.getTelephone()<<endl
        <<user.getGender()<<endl
        <<user.getBirthDate()<<endl;
    }

    fs.close();
}

vector<Department>* DataSource::getDepartmentsPtr(){
    return &departments;
}

vector<Appointment>* DataSource::getAppointmentsPtr(){
    return &appointments;
}
