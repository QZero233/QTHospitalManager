#include "AddAppointmentDialog.h"
#include "ui_AddAppointmentDialog.h"

#include "DepartmentService.h"
#include "DoctorService.h"
#include "AppointmentService.h"

#include <QMessageBox>

AddAppointmentDialog::AddAppointmentDialog(User user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAppointmentDialog),
    user(user)
{
    ui->setupUi(this);
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
    appointment.setDutyId(dutyId);
    appointment.setUsername(user.getUsername());

    if(timePeriod==-1)
        appointment.setTimePeriod(timePeriods[ui->comboBox_time_period->currentIndex()]);
    else
        appointment.setTimePeriod(timePeriod);

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

void AddAppointmentDialog::setTimePeriod(int timePeriod){
    this->timePeriod=timePeriod;
    ui->comboBox_time_period->setVisible(false);
    ui->label_period->setText(QString("预约时间：")+Appointment::toStringPeriod(timePeriod).c_str());
}
