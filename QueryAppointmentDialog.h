#ifndef QUERYAPPOINTMENTDIALOG_H
#define QUERYAPPOINTMENTDIALOG_H

#include <QDialog>
#include "AppointmentService.h"

namespace Ui {
class QueryAppointmentDialog;
}

class QueryAppointmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryAppointmentDialog(QWidget *parent = nullptr);
    ~QueryAppointmentDialog();

    vector<Appointment> getSatisfiedAppointments();

private:
    Ui::QueryAppointmentDialog *ui;
};

#endif // QUERYAPPOINTMENTDIALOG_H
