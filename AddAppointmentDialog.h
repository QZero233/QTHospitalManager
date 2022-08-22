#ifndef ADDAPPOINTMENTDIALOG_H
#define ADDAPPOINTMENTDIALOG_H

#include <QDialog>

#include "Duty.h"
#include "Appointment.h"

namespace Ui {
class AddAppointmentDialog;
}

class AddAppointmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAppointmentDialog(QWidget *parent = nullptr);
    ~AddAppointmentDialog();

    void setDuty(Duty duty);
    Appointment getInputAppointment();

private slots:
    void on_comboBox_time_period_activated(int index);

private:
    Ui::AddAppointmentDialog *ui;

    int dutyId;

    vector<int> timePeriods;

    vector<int> fullIndexes;
};

#endif // ADDAPPOINTMENTDIALOG_H
