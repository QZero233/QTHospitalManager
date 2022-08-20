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

private:
    Ui::AddAppointmentDialog *ui;

    int dutyId;
};

#endif // ADDAPPOINTMENTDIALOG_H
