#include "RegistrationWindow.h"
#include "ui_RegistrationWindow.h"

#include "InputPasswordDialog.h"

#include "DepartmentService.h"
#include "DepartmentDelegate.h"

#include <QMessageBox>

#include "DutyService.h"
#include "ShowDepartmentDutiesDialog.h"
#include "QueryAppointmentDialog.h"
#include "ShowAppointmentsDialog.h"

#include "SelectDutyDialog.h"

#include <QCloseEvent>

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    DepartmentService service;
    model=new DepartmentModel(service.getAllDepartments());

    ui->dataTable->setModel(model);
    ui->dataTable->setItemDelegate(new DepartmentDelegate());
    ui->dataTable->setColumnWidth(4,120);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->dataTable->setGeometry(5,5,x*0.99,y*0.99);
}

void RegistrationWindow::on_actionSelect_triggered()
{
    SelectDutyDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        ShowDepartmentDutiesDialog d(dialog.getSatsfitedDuties());
        d.exec();
    }
}

void RegistrationWindow::on_dataTable_doubleClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;
    //Double click to department duties
    Department department=model->getDepartmentByIndex(index.row());
    ShowDepartmentDutiesDialog dialog(DutyService()
                                      .getAllByDepartmentId(department.getId()));
    dialog.exec();
}

void RegistrationWindow::on_actionQueryAppointment_triggered()
{
    QueryAppointmentDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        vector<Appointment> appointments=dialog.getSatisfiedAppointments();
        if(appointments.size()==0){
            QMessageBox::critical(this,"错误","找不到符合条件的预约");
            return;
        }
        ShowAppointmentsDialog d(appointments);
        d.setAllowDelete();
        d.exec();
    }
}

void RegistrationWindow::closeEvent(QCloseEvent* event){
    try{
        DataSource* dataSource=DataSource::getInstance();
        dataSource->saveToFile();
    }catch(exception& e){
        int ret=QMessageBox::question(this,"是否关闭","自动保存失败，现在关闭将引发数据损失");
        if(ret!=QMessageBox::Yes){
            event->ignore();
        }else{
            event->accept();
        }
    }
}
