#include "ShowTimeDutyDialog.h"
#include "ui_ShowTimeDutyDialog.h"

#include "TimeDutyDelegate.h"

#include "ShowDepartmentDutiesDialog.h"

#include "DepartmentService.h"
#include "AddAppointmentDialog.h"

#include "GlobalTempStorage.h"
#include "AppointmentService.h"

#include <QMessageBox>
#include <QSizePolicy>

ShowTimeDutyDialog::ShowTimeDutyDialog(User user,int departmentId,vector<Duty> duties,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowTimeDutyDialog),
    user(user),
    departmentId(departmentId)

{
    ui->setupUi(this);

    model=new TimeDutyModel(duties,QDate::currentDate());

    ui->dataTable->setModel(model);
    ui->dataTable->setItemDelegate(new TimeDutyDelegate());

    setFixedSize(this->width(), this->height());

    Department department=DepartmentService().getDepartment(departmentId);
    ui->label_department->setText(QString("科室：")+department.getName().c_str());
    ui->dateEdit_date->setDate(QDate::currentDate());
}

ShowTimeDutyDialog::~ShowTimeDutyDialog()
{
    delete ui;
}

void ShowTimeDutyDialog::on_dataTable_doubleClicked(const QModelIndex &index)
{
    if(model->data(index.siblingAtColumn(2),Qt::EditRole).toBool()){
        QMessageBox::critical(this,"错误","该时段预约已满，不再接受预约");
        return;
    }

    //TODO Show dialog
    try {
        Duty duty=model->getByIndex(index.row());
        AddAppointmentDialog dialog(user);
        dialog.setDuty(duty);
        if(dialog.exec()==QDialog::Accepted){
            AppointmentService().addAppointment(dialog.getInputAppointment());
        }
    }  catch (exception& e) {
        QMessageBox::critical(this,"错误",e.what());
    }

    //ShowDepartmentDutiesDialog dialog(timePeriod,user,duties);
    //dialog.exec();
}

void ShowTimeDutyDialog::on_dateEdit_date_userDateChanged(const QDate &date)
{
    model->setCurrentDate(date);
}
