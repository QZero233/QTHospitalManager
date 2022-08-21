#include "SelectDutyDialog.h"
#include "ui_SelectDutyDialog.h"

#include "AppointmentService.h"

SelectDutyDialog::SelectDutyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDutyDialog)
{
    ui->setupUi(this);

    //Setup data
    ui->comboBox_time->addItem("上午");
    ui->comboBox_time->addItem("下午");

    ui->dateEdit_date->setDate(QDate::currentDate());
    ui->dateEdit_date->setCalendarPopup(true);

    //Load department data
    departments=DepartmentService().getAllDepartments();
    for(Department department:departments){
        ui->comboBox_department->addItem(department.getName().c_str());
    }
    on_comboBox_department_activated(0);

    ui->checkBox_free->setChecked(true);
}

SelectDutyDialog::~SelectDutyDialog()
{
    delete ui;
}

vector<Duty> SelectDutyDialog::getSatsfitedDuties(){
    vector<Duty> duties=DutyService().getAllDuties();
    vector<Duty> result;

    int departmentId=departments[ui->comboBox_department->currentIndex()].getId();
    int doctorId=-1;
    if(ui->comboBox_doctor->currentIndex()!=0){
        doctorId=doctors[ui->comboBox_doctor->currentIndex()-1].getId();
    }

    DoctorService service;
    for(Duty duty:duties){
        Doctor doctor=service.getDoctor(duty.getDoctorId());
        if(doctor.getDepartmentId()!=departmentId)
            continue;

        if(doctorId!=-1 && doctorId!=duty.getDoctorId())
            continue;

        if(!ui->checkBox_no_time->isChecked()){
            long long date=ui->dateEdit_date->date().toJulianDay();
            int time=ui->comboBox_time->currentIndex()==0?
                        Duty::TIME_AM:Duty::TIME_PM;

            if(date!=duty.getDutyDate() || time!=duty.getDutyTime())
                continue;
        }

        if(ui->checkBox_free->isChecked()){
            //Check if the duty is free
            if(AppointmentService().existByDutyId(duty.getId()))
                continue;
        }

        result.push_back(duty);
    }

    return result;
}

void SelectDutyDialog::on_checkBox_no_time_stateChanged(int arg1)
{
    ui->dateEdit_date->setEnabled(arg1==Qt::Unchecked);
    ui->comboBox_time->setEnabled(arg1==Qt::Unchecked);
}

void SelectDutyDialog::on_comboBox_department_activated(int index)
{
    //Change doctor combobox
    vector<Doctor> allDoctors=DoctorService().getAllDoctors();
    doctors.clear();
    int departmentId=departments[index].getId();

    ui->comboBox_doctor->clear();
    ui->comboBox_doctor->addItem("不限医生");
    for(Doctor doctor:allDoctors){
        if(doctor.getDepartmentId()==departmentId){
            doctors.push_back(doctor);
            ui->comboBox_doctor->addItem(doctor.getName().c_str());
        }
    }

}
