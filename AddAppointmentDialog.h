#ifndef ADDAPPOINTMENTDIALOG_H
#define ADDAPPOINTMENTDIALOG_H

#include <QDialog>

#include "Duty.h"
#include "Appointment.h"
#include "User.h"

namespace Ui {
class AddAppointmentDialog;
}

class AddAppointmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAppointmentDialog(User user,QWidget *parent = nullptr);
    ~AddAppointmentDialog();

    void setDuty(Duty duty);
    void setTimePeriod(int timePeriod);
    Appointment getInputAppointment();

private slots:
    void on_comboBox_time_period_activated(int index);

private:
    Ui::AddAppointmentDialog *ui;

    int dutyId;

    vector<int> timePeriods;

    vector<int> fullIndexes;

    User user;

    int timePeriod=-1;
};

#endif // ADDAPPOINTMENTDIALOG_H
