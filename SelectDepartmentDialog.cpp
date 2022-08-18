#include "SelectDepartmentDialog.h"
#include "ui_SelectDepartmentDialog.h"

#include <QIntValidator>

SelectDepartmentDialog::SelectDepartmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDepartmentDialog)
{
    ui->setupUi(this);

    ui->lineEdit_id->setValidator(new QIntValidator());
    ui->dateTimeEdit_time->setDateTime(QDateTime::currentDateTime());

    ui->checkBox_id->setChecked(false);
    ui->checkBox_capacity->setChecked(false);
    ui->checkBox_time->setChecked(false);
}

SelectDepartmentDialog::~SelectDepartmentDialog()
{
    delete ui;
}

void SelectDepartmentDialog::on_checkBox_time_stateChanged(int arg1)
{
    ui->label_time->setVisible(arg1==Qt::Checked);
    ui->dateTimeEdit_time->setVisible(arg1==Qt::Checked);
    enableTime=arg1==Qt::Checked;
}

void SelectDepartmentDialog::on_checkBox_id_stateChanged(int arg1)
{
    ui->label_id->setVisible(arg1==Qt::Checked);
    ui->lineEdit_id->setVisible(arg1==Qt::Checked);
    enableId=arg1==Qt::Checked;
}

void SelectDepartmentDialog::on_checkBox_capacity_stateChanged(int arg1)
{
    ui->label_capacity->setVisible(arg1==Qt::Checked);
    ui->spinBox_capacity->setVisible(arg1==Qt::Checked);
    enableCapacity=arg1==Qt::Checked;
}

vector<Department> SelectDepartmentDialog::getSatisfiedDepartments(){
    DepartmentService service;
    vector<Department> all=service.getAllDepartments();

    long time=ui->dateTimeEdit_time->time().msecsSinceStartOfDay();
    int id=ui->lineEdit_id->text().toInt();
    int capacity=ui->spinBox_capacity->value();

    vector<Department> result;
    for(Department department:all){
        if(enableTime &&
                (time<=department.getAppointmentStartTime() || time>=department.getAppointmentEndTime()))
            continue;

        if(enableId && department.getIdOfDutyDoctor()!=id)
            continue;

        if(enableCapacity){
            int remainCapacity=department.getCapacity()-
                    service.getAppointmentCountById(department.getId());

            if(remainCapacity<capacity)
                continue;
        }

        result.push_back(department);
    }

    return result;
}
