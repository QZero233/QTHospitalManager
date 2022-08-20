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

RegistrationWindow::RegistrationWindow(MainWindow* win,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow),
    win(win)
{
    ui->setupUi(this);

    //TODO fill table with departments
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

void RegistrationWindow::closeEvent(QCloseEvent* event){
    QMessageBox::critical(this,"失败","请使用工具栏上的退出按钮退出");
    event->ignore();
}

void RegistrationWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->dataTable->setGeometry(5,5,x*0.99,y*0.99);
}

void RegistrationWindow::on_actionExit_triggered()
{
    InputPasswordDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        QString pwd=dialog.getPwd();
        //TODO let admin set password
        if(pwd=="1"){
            //Exit
            win->show();
            delete this;
        }else{
            QMessageBox::critical(this,"退出失败","密码不正确");
        }
    }
}

void RegistrationWindow::on_actionSelect_triggered()
{

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
