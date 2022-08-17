#ifndef ADDAPPOINTMENTDIALOG_H
#define ADDAPPOINTMENTDIALOG_H

#include <QDialog>

#include "DepartmentService.h"
#include "AppointmentService.h"

namespace Ui {
class AddAppointmentDialog;
}

class AddAppointmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAppointmentDialog(int departmentId,QWidget *parent = nullptr);
    ~AddAppointmentDialog();

    Appointment getCurrentStored(){return currentStored;}
private slots:
    void on_pushButton_clicked();

private:
    Ui::AddAppointmentDialog *ui;

    AppointmentService service;

    void accept() override;

    Appointment currentStored;
};

#endif // ADDAPPOINTMENTDIALOG_H
