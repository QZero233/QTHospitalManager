#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include <iostream>

#include <QStringList>
#include <QStandardItem>
#include <QMessageBox>
#include <QTime>
#include <QFileDialog>
#include <QDir>

#include "AppointmentService.h"

#include "TimeUtils.h"

#include "departmenteditdialog.h"
#include "ShowAppointmentsDialog.h"
#include "InputTelDialog.h"

#include "DoctorService.h"
#include "DutyService.h"

#include "RegistrationWindow.h"

#include "DepartmentDelegate.h"
#include "DutyDelegate.h"

#include "AddDoctorDialog.h"
#include "AddDutyDialog.h"
#include "AddUserDialog.h"
#include "SelectDateDialog.h"
#include "DoctorStatisticDialog.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set up toolbar
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //Set table not editable
    ui->dataTable->setItemDelegate(delegate);

    ui->dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Add right-click menu
    tableMenu=new QMenu(ui->dataTable);
    editAction=new QAction("编辑",ui->dataTable);
    deleteAction=new QAction("删除",ui->dataTable);
    appointmentsAction=new QAction("查看预约",ui->dataTable);
    tableMenu->addAction(editAction);
    tableMenu->addAction(deleteAction);
    tableMenu->addAction(appointmentsAction);
    ui->dataTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->dataTable,SIGNAL(customContextMenuRequested(QPoint)),this,
            SLOT(dataTable_customContextMenuRequested(QPoint)));
    connect(editAction,SIGNAL(triggered()),this,SLOT(dataTable_edit_triggered()));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(dataTable_delete_triggered()));
    connect(appointmentsAction,SIGNAL(triggered()),this,SLOT(dataTable_appointments_triggered()));

    model=new DepartmentModel(departmentService.getAllDepartments());
    ui->dataTable->setModel(model);

    controlMenuVisibilityByMode();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dataTable_customContextMenuRequested(QPoint pos){
    QModelIndex index=ui->dataTable->indexAt(pos);

    if(index.isValid()){
        if(mode==MODE_DEPARTMENT){
            editAction->setVisible(true);
            appointmentsAction->setVisible(true);
        }else{
            editAction->setVisible(false);
            appointmentsAction->setVisible(false);
        }

        contextMenuSelectedIndex=index.row();
        selectedColumn=index.column();


        tableMenu->exec(QCursor::pos());
    }
}

void MainWindow::dataTable_edit_triggered(){
    if(contextMenuSelectedIndex<0)
        return;

    showEditDepartmentDialog(model->getDepartmentByIndex(contextMenuSelectedIndex).getId());
}

void MainWindow::dataTable_delete_triggered(){
    if(mode==MODE_DEPARTMENT){
        //Show confirm dialog
        Department department=model->getDepartmentByIndex(contextMenuSelectedIndex);

        QMessageBox box;
        box.setText(("是否删除门诊部门 "+department.getName()).c_str());
        box.setInformativeText("此操作不可逆！");
        box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Ok);
        int ret=box.exec();
        if(ret==QMessageBox::Ok){
            //Delete
            try{
                model->deleteDepartment(contextMenuSelectedIndex);
            }catch(exception& e){
                QMessageBox::critical(this,"删除失败",e.what());
            }
        }
    }else if(mode==MODE_DOCTOR){
        //Show confirm dialog
        Doctor doctor=doctorModel->getDoctorByIndex(contextMenuSelectedIndex);

        QMessageBox box;
        box.setText(("是否删除医生 "+doctor.getName()).c_str());
        box.setInformativeText("此操作不可逆！");
        box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Ok);
        int ret=box.exec();
        if(ret==QMessageBox::Ok){
            //Delete
            try{
                doctorModel->deleteDoctor(contextMenuSelectedIndex);
            }catch(exception& e){
                QMessageBox::critical(this,"删除失败",e.what());
            }
        }
    }else if(mode==MODE_DUTY){
        //Show confirm dialog
        QMessageBox box;
        box.setText("是否删除该排班");
        box.setInformativeText("此操作不可逆！");
        box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Ok);
        int ret=box.exec();
        if(ret==QMessageBox::Ok){
            //Delete
            try{
                dutyModel->deleteDuty(contextMenuSelectedIndex,selectedColumn);
            }catch(exception& e){
                QMessageBox::critical(this,"删除失败",e.what());
            }
        }
    }else if(mode==MODE_USER){
        //Show confirm dialog
        User user=userModel->getUserByIndex(contextMenuSelectedIndex);

        QMessageBox box;
        box.setText(("是否删除用户"+user.getUsername()).c_str());
        box.setInformativeText("此操作不可逆！");
        box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Ok);
        int ret=box.exec();
        if(ret==QMessageBox::Ok){
            //Delete
            try{
                userModel->deleteUser(contextMenuSelectedIndex);
            }catch(exception& e){
                QMessageBox::critical(this,"删除失败",e.what());
            }
        }
    }

}

void MainWindow::dataTable_appointments_triggered(){
    showAppointmentsDialog(model->getDepartmentByIndex(contextMenuSelectedIndex).getId());
}

void MainWindow::showEditDepartmentDialog(int id){
    Department department=departmentService.getDepartment(id);

    DepartmentEditDIalog dialog;
    dialog.setIdEditable(false);
    dialog.setPreset(department);
    int ret=dialog.exec();
    if(ret==QDialog::Accepted){
        try {
            //Update
            departmentService.updateDepartment(dialog.getStored());
            //Flush UI
            model->reloadFromDataSource();
        }  catch(exception& e) {
            QMessageBox::critical(this,"修改失败",e.what());
        }
    }
}

void MainWindow::showAppointmentsDialog(int id){
    ShowAppointmentsDialog dialog(AppointmentService().
                                  getAllAppointmentsByDepartmentId(id));
    dialog.setAllowDelete();
    dialog.exec();
    model->reloadFromDataSource();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->dataTable->setGeometry(5,5,x*0.99,y*0.99);
}

void MainWindow::on_dataTable_doubleClicked(const QModelIndex &index)
{
    if(mode==MODE_DEPARTMENT){
        int id=index.sibling(index.row(),0).data().toInt();
        if(index.column()==4){
            showAppointmentsDialog(id);
        }else{
            showEditDepartmentDialog(id);
        }
    }else if(mode==MODE_STATISTIC){
        Department department=statisticModel->getDepartmentByIndex(index.row());
        DoctorStatisticDialog dialog(department.getId());
        dialog.exec();
    }
}

void MainWindow::closeEvent(QCloseEvent* event){
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

void MainWindow::on_actionAdd_triggered()
{
    //Get suitable id for it
    int biggestId=0;
    vector<Department> departments=departmentService.getAllDepartments();
    for(Department department:departments){
        if(department.getId()>biggestId)
            biggestId=department.getId();
    }
    biggestId++;


    Department preset(biggestId,"","","" );

    DepartmentEditDIalog dialog;
    dialog.setIdEditable(true);
    dialog.setPreset(preset);
    int ret=dialog.exec();
    if(ret==QDialog::Accepted){
        try {
            //Add
            model->addDepartment(dialog.getStored());
        }  catch(exception& e) {
            QMessageBox::critical(this,"添加失败",e.what());
        }
    }
}

void MainWindow::on_actionduties_triggered()
{
    mode=MODE_DUTY;
    vector<Duty> duties=DutyService().getAllDuties();

    if(dutyModel==NULL){
        dutyModel=new TableDutyModel(duties,QDate::currentDate(),5);
    }else{
        dutyModel->setDutiesAndReload(duties);
    }

    ui->dataTable->setModel(dutyModel);
    ui->dataTable->setItemDelegate(new ReadOnlyDelegate());

    controlMenuVisibilityByMode();
}

void MainWindow::on_actiondepartments_triggered()
{
    mode=MODE_DEPARTMENT;

    model->setDepartmentsAndReload(departmentService.getAllDepartments());
    ui->dataTable->setModel(model);
    ui->dataTable->setItemDelegate(delegate);

    controlMenuVisibilityByMode();
}

void MainWindow::on_actiondoctors_triggered()
{
    mode=MODE_DOCTOR;

    vector<Doctor> doctors=DoctorService().getAllDoctors();
    if(doctorModel==NULL){
        doctorModel=new DoctorModel(doctors);
    }else{
        doctorModel->setDoctorsAndReload(doctors);
    }

    if(doctorDelegate!=NULL){
        delete doctorDelegate;
        doctorDelegate=new DoctorDelegate();
    }

    ui->dataTable->setModel(doctorModel);
    ui->dataTable->setItemDelegate(doctorDelegate);

    controlMenuVisibilityByMode();
}

void MainWindow::on_actionaddDoctor_triggered()
{
    AddDoctorDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        try {
            Doctor doctor=dialog.getInputDoctor();
            doctorModel->addDoctor(doctor);
        }  catch (exception& e) {
            QMessageBox::critical(this,"错误",e.what());
        }
    }
}

void MainWindow::on_actionaddDuty_triggered()
{
    AddDutyDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        try {
            dutyModel->addDuty(dialog.getInputDuty());
        }  catch (exception& e) {
            QMessageBox::critical(this,"错误",e.what());
        }
    }
}

void MainWindow::controlMenuVisibilityByMode(){
    ui->actionAdd->setVisible(false);
    ui->actionaddDoctor->setVisible(false);
    ui->actionaddDuty->setVisible(false);
    ui->actionAddUser->setVisible(false);
    ui->actionDate->setVisible(false);

    switch(mode){
    case MODE_DEPARTMENT:
        ui->actionAdd->setVisible(true);
        break;
    case MODE_DOCTOR:
        ui->actionaddDoctor->setVisible(true);
        break;
    case MODE_DUTY:
        ui->actionaddDuty->setVisible(true);
        ui->actionDate->setVisible(true);
        break;
    case MODE_USER:
        ui->actionAddUser->setVisible(true);
        break;
    case MODE_STATISTIC:
        break;
    }
}

void MainWindow::on_actionUsers_triggered()
{
    mode=MODE_USER;

    if(userModel==NULL){
        userModel=new UserModel(UserService().getAllUsers());
    }

    ui->dataTable->setModel(userModel);
    ui->dataTable->setItemDelegate(userDelegate);

    controlMenuVisibilityByMode();
}

void MainWindow::on_actionAddUser_triggered()
{
    AddUserDialog dialog(true);
    if(dialog.exec()==QDialog::Accepted){
        try {
            userModel->addUser(dialog.getInputUser());
        }  catch (exception& e) {
            QMessageBox::critical(this,"错误",e.what());
        }
    }
}

void MainWindow::on_actionStastic_triggered()
{
    mode=MODE_STATISTIC;

    if(statisticModel==NULL){
        statisticModel=new StatisticModel(DepartmentService().getAllDepartments());
    }

    ui->dataTable->setModel(statisticModel);
    ui->dataTable->setItemDelegate(statisticDelegate);

    controlMenuVisibilityByMode();
}

void MainWindow::on_actionDate_triggered()
{
    SelectDateDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        QDate date=dialog.getDate();
        int day=dialog.getDays();

        dutyModel->setDateAndCount(date,day);
    }
}
