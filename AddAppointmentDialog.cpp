#include "AddAppointmentDialog.h"
#include "ui_AddAppointmentDialog.h"

#include <QIntValidator>

AddAppointmentDialog::AddAppointmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAppointmentDialog)
{
    ui->setupUi(this);

    ui->comboBox_gender->addItem("男");
    ui->comboBox_gender->addItem("女");

    ui->lineEdit_id->setValidator(new QIntValidator);
}

AddAppointmentDialog::~AddAppointmentDialog()
{
    delete ui;
}
