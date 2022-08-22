#include "AddAppointmentDialog.h"
#include "ui_AddAppointmentDialog.h"

#include "DepartmentService.h"
#include "DoctorService.h"
#include "AppointmentService.h"

#include <QMessageBox>

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
    ui->label_time->setText(("预约时间："+duty.formatDutyDateAndTimePeriod()).c_str());
    ui->label_doctor->setText(("预约医生："+doctor.getName()+"("+doctorPosition+")").c_str());

    dutyId=duty.getId();

    timePeriods=Appointment::getTimePeriodsByDutyTimePeriod(duty.getDutyTimePeriod());

    AppointmentService appointmentService;
    int i=0;
    for(int period:timePeriods){
        string p=Appointment::toStringPeriod(period);

        //Get status
        int periodCapacity=duty.getCapacityEachPeriod();
        int appointmentCount=appointmentService.getCountByIdAndTimePeriod(duty.getId(),
                                                                          period);

        int remain=periodCapacity-appointmentCount;

        ui->comboBox_time_period->addItem((p+"("+to_string(appointmentCount)+"/"+
                                           to_string(periodCapacity)+")"+
                                           (remain<=0?
                                            "已满":"")).c_str());

        if(remain<=0){
            fullIndexes.push_back(i);
        }

        i++;
    }
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
    appointment.setTimePeriod(timePeriods[ui->comboBox_time_period->currentIndex()]);
    return appointment;
}

void AddAppointmentDialog::on_comboBox_time_period_activated(int index)
{
    for(int i:fullIndexes){
        if(i==index){
            //QMessageBox::critical(this,"错误","请注意，此时段预约已满");
        }
    }
}
