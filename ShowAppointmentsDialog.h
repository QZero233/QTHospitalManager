#ifndef SHOWAPPOINTMENTSDIALOG_H
#define SHOWAPPOINTMENTSDIALOG_H

#include <QDialog>

#include <QStandardItemModel>
#include <QStandardItem>

#include "AppointmentService.h"

namespace Ui {
class ShowAppointmentsDialog;
}

class ShowAppointmentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAppointmentsDialog(int departmentId,QWidget *parent = nullptr);
    ~ShowAppointmentsDialog();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ShowAppointmentsDialog *ui;

    int departmentId;

    void displayAppointments();

    QStandardItemModel* model;

    AppointmentService service;
};

#endif // SHOWAPPOINTMENTSDIALOG_H
