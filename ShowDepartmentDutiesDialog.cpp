#include "ShowDepartmentDutiesDialog.h"
#include "ui_ShowDepartmentDutiesDialog.h"

#include "DutyDelegate.h"
#include "AddAppointmentDialog.h"
#include "AppointmentService.h"

#include <QMessageBox>

ShowDepartmentDutiesDialog::ShowDepartmentDutiesDialog(vector<Duty> duties,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowDepartmentDutiesDialog)
{
    ui->setupUi(this);

    model=new DutyModel(duties);

    ui->dataTable->setModel(model);
    ui->dataTable->setItemDelegate(new DutyDelegate());

    ui->dataTable->setColumnWidth(2,120);
}

ShowDepartmentDutiesDialog::~ShowDepartmentDutiesDialog()
{
    delete ui;
}

void ShowDepartmentDutiesDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->dataTable->setGeometry(5,5,x*0.99,y*0.99);
}

void ShowDepartmentDutiesDialog::on_dataTable_doubleClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    Duty duty=model->getDutyByIndex(index.row());

    int capacity=DutyService().getCapacityById(duty.getId());
    int appointment=AppointmentService().getCountByDutyId(duty.getId());

    if(capacity-appointment<=0){
        QMessageBox::critical(this,"错误","此时段已被预约");
        return;
    }

    AddAppointmentDialog dialog;
    dialog.setDuty(duty);
    if(dialog.exec()==QDialog::Accepted){
        try{
            AppointmentService().addAppointment(dialog.getInputAppointment());
        }catch(exception& e){
            QMessageBox::critical(this,"错误",e.what());
        }
    }
}
