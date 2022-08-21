#include "AddAppointmentDialog.h"
#include "ui_AddAppointmentDialog.h"

#include "DepartmentService.h"
#include "DoctorService.h"
#include "AppointmentService.h"

AddAppointmentDialog::AddAppointmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAppointmentDialog)
{
    ui->setupUi(this);

    ui->comboBox_gender->addItem("男");
    ui->comboBox_gender->addItem("女");
}



AddAppointmentDialog::~AddAppointmentDialog()
{
    delete ui;
}

void AddAppointmentDialog::setDuty(Duty duty){
    Doctor doctor=DoctorService().getDoctor(duty.getDoctorId());
    Department department=DepartmentService().getDepartment(doctor.getDepartmentId());

    string doctorPosition;
    switch(doctor.getPosition()){
    case Doctor::POSITION_PRACTICE:
        doctorPosition="实习医师";
        break;
    case Doctor::POSITION_JUNIOR:
        doctorPosition="高级医师";
        break;
    case Doctor::POSITION_SENIOR:
        doctorPosition="领域专家";
        break;
    }

    ui->label_depaerment->setText(("预约科室："+department.getName()).c_str());
    ui->label_time->setText(("预约时间："+duty.formatDutyDateTime()).c_str());
    ui->label_doctor->setText(("预约医生："+doctor.getName()+"("+doctorPosition+")").c_str());

    dutyId=duty.getId();
}

Appointment AddAppointmentDialog::getInputAppointment(){
    AppointmentService service;
    Appointment appointment;
    appointment.setId(service.getUniqueId());
    appointment.setName(ui->lineEdit_name->text().toStdString());
    appointment.setTelephone(ui->lineEdit_tel->text().toStdString());
    appointment.setAge(ui->spinBox_age->value());
    appointment.setDutyId(dutyId);
    appointment.setGender(ui->comboBox_gender->currentIndex()==0?
                              Appointment::GENDER_MALE:Appointment::GENDER_FEMALE);
    return appointment;
}
