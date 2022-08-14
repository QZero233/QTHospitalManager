#include "ShowAppointmentsDialog.h"
#include "ui_ShowAppointmentsDialog.h"

#include "AppointmentEditDelegate.h"

#include <QStringList>

#include "TimeUtils.h"

ShowAppointmentsDialog::ShowAppointmentsDialog(int departmentId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAppointmentsDialog),
    departmentId(departmentId)
{
    ui->setupUi(this);

    model=new QStandardItemModel();
    ui->dataTable->setModel(model);

    AppointmentEditDelegate* delegate=new AppointmentEditDelegate(departmentId);
    //ui->dataTable->setItemDelegateForColumn(0,delegate);
    ui->dataTable->setItemDelegate(delegate);

    displayAppointments();

}

ShowAppointmentsDialog::~ShowAppointmentsDialog()
{
    delete ui;
}

void ShowAppointmentsDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->dataTable->setGeometry(5,5,x*0.99,y*0.99);
}

void ShowAppointmentsDialog::displayAppointments(){
    model->clear();

    //Set header
    QStringList list;
    list.append("编号");
    list.append("姓名");
    list.append("性别");
    list.append("年龄");
    list.append("预约时间");
    list.append("电话");
    model->setHorizontalHeaderLabels(list);

    //Fill data
    vector<Appointment> appointments=service.getAllAppointments(departmentId);

    QStandardItem* item;
    for(int i=0;i<appointments.size();i++){
        Appointment appointment=appointments[i];

        item=new QStandardItem(QString("%1").arg(appointment.getId()));
        model->setItem(i,0,item);

        item=new QStandardItem(QString(appointment.getName().c_str()));
        model->setItem(i,1,item);

        item=new QStandardItem(QString(appointment.getGender()==Appointment::GENDER_MALE?"男":"女"));
        model->setItem(i,2,item);

        item=new QStandardItem(QString::number(appointment.getAge()));
        model->setItem(i,3,item);

        item=new QStandardItem(TimeUtils::formatTimeStamp(appointment.getAppointmentTime()));
        model->setItem(i,4,item);

        item=new QStandardItem(QString(appointment.getTelephone().c_str()));
        model->setItem(i,5,item);
    }

    ui->dataTable->setColumnWidth(4,100);
    ui->dataTable->setColumnWidth(5,100);
}
