#include "QueryAppointmentDialog.h"
#include "ui_QueryAppointmentDialog.h"

#include "ShowAppointmentsDialog.h"

QueryAppointmentDialog::QueryAppointmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryAppointmentDialog)
{
    ui->setupUi(this);
}

QueryAppointmentDialog::~QueryAppointmentDialog()
{
    delete ui;
}

vector<Appointment> QueryAppointmentDialog::getSatisfiedAppointments(){
    string name=ui->lineEdit_name->text().toStdString();
    string tel=ui->lineEdit_tel->text().toStdString();

    vector<Appointment> appointments=AppointmentService().getAllAppointmentsByNameAndTelephone(name,tel);
    return appointments;
}
