#include "AddDutyDialog.h"
#include "ui_AddDutyDialog.h"

#include "DutyService.h"

#include <QIntValidator>

AddDutyDialog::AddDutyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDutyDialog)
{
    ui->setupUi(this);

    ui->dateEdit_date->setDate(QDate::currentDate());

    ui->comboBox_time->addItem("上午");
    ui->comboBox_time->addItem("下午");

    doctors=DoctorService().getAllDoctors();
    for(Doctor doctor:doctors){
        ui->comboBox_doctor->addItem(doctor.getName().c_str());
    }

    ui->lineEdit_capacity->setValidator(new QIntValidator());
    ui->lineEdit_capacity->setText("10");
}

AddDutyDialog::~AddDutyDialog()
{
    delete ui;
}

Duty AddDutyDialog::getInputDuty(){
    Duty duty;

    duty.setId(DutyService().getUniqueId());
    duty.setDoctorId(doctors[ui->comboBox_doctor->currentIndex()].getId());
    duty.setDutyDate(ui->dateEdit_date->date().toJulianDay());
    duty.setDutyTimePeriod(ui->comboBox_time->currentIndex()==0?
                               Duty::TIME_PERIOD_AM:Duty::TIME_PERIOD_PM);
    duty.setCapacityEachPeriod(ui->lineEdit_capacity->text().toInt());

    return duty;
}
