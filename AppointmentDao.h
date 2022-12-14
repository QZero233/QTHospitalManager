#ifndef APPOINTMENTDAO_H
#define APPOINTMENTDAO_H

#include "DataSource.h"

class AppointmentDao
{
public:
    AppointmentDao(){
        appointmentsPtr=DataSource::getInstance()->getAppointmentsPtr();
    }

    int getIndexById(int id) throw(runtime_error);
    bool existById(int id);
    void addAppointment(const Appointment& appointment) throw(invalid_argument);
    void deleteAppointment(int id);
    void updateAppointment(const Appointment& appointment);
    Appointment getAppointment(int id);

    vector<Appointment> getAllAppointments();

    bool existByDutyId(int dutyId);

private:
    vector<Appointment>* appointmentsPtr;
};

#endif // APPOINTMENTDAO_H
