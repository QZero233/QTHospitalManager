#pragma once
#ifndef STORAGE_UTILS
#define STORAGE_UTILS

#include "Department.h"

#include <string>
#include <vector>

#include <fstream>

using namespace std;

class StorageUtils {
public:
    /*
     * int id;
    string name;
    int idOfDutyDoctor;
    long appointmentStartTime;
    long appointmentEndTime;
    int capacity;
    string address;
    string telephone;

    vector<Appointment> appointments;
     */
	static void saveRecordToFile(string fileName, vector<Department>& departments) {
        /*fstream fs(fileName.c_str(),ios::out);
        for(Department department:departments){
            fs<<department.getId()<<endl
             <<department.getName()<<endl
            <<department.getIdOfDutyDoctor()<<endl
            <<department.getAppointmentStartTime()<<endl
            <<department.getAppointmentEndTime()<<endl
            <<department.getCapacity()<<endl
            <<department.getAddress()<<endl
            <<department.getTelephone()<<endl;

            //Write appointments
            vector<Appointment>* appointments=department.getAppointmentsPtr();
            for(int i=0;i<appointments->size();i++){
                Appointment appointment=appointments->at(i);*/
                /*
                 * int id;
                    string name;
                    string telephone;
                int gender;
                int age;
                     long appointmentTime;
                 */
                /*fs<<appointment.getId()<<endl
                 <<appointment.getName()<<endl
                <<appointment.getTelephone()<<endl
                <<appointment.getGender()<<endl
                <<appointment.getAge()<<endl
                <<appointment.getAppointmentTime()<<endl;
            }
            fs<<-1<<endl;
        }

        fs<<-1;

        fs.close();*/
	}

    /*
     * int id;
    string name;
    int idOfDutyDoctor;
    long appointmentStartTime;
    long appointmentEndTime;
    int capacity;
    string address;
    string telephone;

    vector<Appointment> appointments;
     */
	static vector<Department> readRecordFromFile(string fileName) {
        /*fstream fs(fileName.c_str(),ios::in);
        if(!fs)
            return vector<Department>();

        vector<Department> result;

        while(true){
            int id;
            string name;
            int idOfDutyDoctor;
            long appointmentStartTime;
            long appointmentEndTime;
            int capacity;
            string address;
            string telephone;

            fs>>id;
            if(id<0)
                break;
            fs>>name>>idOfDutyDoctor>>appointmentStartTime>>appointmentEndTime>>capacity>>address>>telephone;*/

            //Load appointments
            /*
             * int id;
                string name;
                string telephone;
            int gender;
            int age;
                 long appointmentTime;
             */

            /*vector<Appointment> appointments;
            while(true){
                int id;
                string name;
                string telephone;
                int gender;
                int age;
                long appointmentTime;

                fs>>id;
                if(id<0)
                    break;//End of record

                fs>>name>>telephone>>gender>>age>>appointmentTime;

                Appointment appointment;
                appointment.setId(id);
                appointment.setName(name);
                appointment.setTelephone(telephone);
                appointment.setGender(gender);
                appointment.setAge(age);
                appointment.setAppointmentTime(appointmentTime);
                appointments.push_back(appointment);
            }

            Department department(id,name,idOfDutyDoctor,appointmentStartTime,appointmentEndTime,
                                  capacity,address,telephone);
            department.setAppointments(appointments);

            result.push_back(department);
        }


        fs.close();
        return result;*/

        return vector<Department>();
	}
};



#endif
