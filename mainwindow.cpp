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

using namespace std;

//TODO check dependent relationship when deleting
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set up toolbar
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //Set table not editable
    ui->dataTable->setItemDelegate(delegate);

    //Add right-click menu
    tableMenu=new QMenu(ui->dataTable);
    editAction=new QAction("编辑",ui->dataTable);
    deleteAction=new QAction("删除",ui->dataTable);
    appointmentsAction=new QAction("查看预约",ui->dataTable);
    tableMenu->addAction(editAction);
    //tableMenu->addAction(deleteAction);
    tableMenu->addAction(appointmentsAction);
    ui->dataTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->dataTable,SIGNAL(customContextMenuRequested(QPoint)),this,
            SLOT(dataTable_customContextMenuRequested(QPoint)));
    connect(editAction,SIGNAL(triggered()),this,SLOT(dataTable_edit_triggered()));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(dataTable_delete_triggered()));
    connect(appointmentsAction,SIGNAL(triggered()),this,SLOT(dataTable_appointments_triggered()));

    //

    //Disable some menus before opening
    ui->actionSave->setVisible(false);
    ui->actionAdd->setVisible(false);
    ui->actionRegistration->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dataTable_customContextMenuRequested(QPoint pos){
    QModelIndex index=ui->dataTable->indexAt(pos);

    if(index.isValid()){
        contextMenuSelectedIndex=index.row();

        if(mode==MODE_DEPARTMENT){
            tableMenu->exec(QCursor::pos());
        }
    }
}

void MainWindow::dataTable_edit_triggered(){
    if(contextMenuSelectedIndex<0)
        return;

    showEditDepartmentDialog(model->getDepartmentByIndex(contextMenuSelectedIndex).getId());
}

void MainWindow::dataTable_delete_triggered(){
    //Show confirm dialog
    Department department=model->getDepartmentByIndex(contextMenuSelectedIndex);

    QMessageBox box;
    box.setText(("是否删除患门诊部门 "+department.getName()).c_str());
    box.setInformativeText("此操作不可逆！");
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Ok);
    int ret=box.exec();
    if(ret==QMessageBox::Ok){
        //Delete
        try{
            model->deleteDepartment(contextMenuSelectedIndex);
            saved=false;
        }catch(exception& e){
            QMessageBox::critical(this,"删除失败",e.what());
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

            saved=false;
        }  catch(exception& e) {
            QMessageBox::critical(this,"修改失败",e.what());
        }
    }
}

void MainWindow::showAppointmentsDialog(int id){
    ShowAppointmentsDialog dialog(AppointmentService().
                                  getAllAppointmentsByDepartmentId(id));
    dialog.exec();
    model->reloadFromDataSource();
    saved=false;
}

void addTestData(){
    //Add 5 departments
    DepartmentService departmentService;
    for(int i=1;i<=5;i++){
        Department department(i,"科室"+to_string(i),"地址1"+to_string(i),"电话1"+to_string(i));
        departmentService.addDepartment(department);
    }

    //Add 10 doctors
    DoctorService doctorService;
    for(int i=1;i<=10;i++){
        int position=Doctor::POSITION_PRACTICE;
        if(i%3==1)
            position=Doctor::POSITION_SENIOR;
        else if(i%3==2)
            position=Doctor::POSITION_JUNIOR;

        Doctor doctor(i,"医生"+to_string(i),position);
        doctorService.addDoctor(doctor);
    }

    //Add 6 duties
    DutyService dutyService;
    long long today=QDate::currentDate().toJulianDay();
    dutyService.addDuty(Duty(1,1,2,Duty::TIME_AM,today));
    dutyService.addDuty(Duty(2,1,2,Duty::TIME_PM,today));
    dutyService.addDuty(Duty(3,3,1,Duty::TIME_AM,today));
    dutyService.addDuty(Duty(4,4,1,Duty::TIME_PM,today));
    dutyService.addDuty(Duty(5,5,4,Duty::TIME_AM,today));
    dutyService.addDuty(Duty(6,6,5,Duty::TIME_PM,today));

    //Add 10 appointments
    AppointmentService appointmentService;
    appointmentService.addAppointment(Appointment(1,"预约1","电话1",0,18,2));
    appointmentService.addAppointment(Appointment(2,"预约2","电话2",1,18,5));
}

void MainWindow::on_actionOpen_triggered()
{
    //Init data source
    DataSource* dataSource=DataSource::getInstance();
    dataSource->setStorageFilePath("record.txt");
    //dataSource->loadFromFile();
    addTestData();

    model=new DepartmentModel(departmentService.getAllDepartments());
    ui->dataTable->setModel(model);

    ui->actionOpen->setVisible(false);

    ui->actionSave->setVisible(true);
    ui->actionAdd->setVisible(true);
    ui->actionRegistration->setVisible(true);

    //ui->dataTable->setColumnWidth(4,120);
    //ui->dataTable->setColumnWidth(5,100);
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
    }
}

void MainWindow::on_actionSave_triggered()
{
    DataSource* dataSource=DataSource::getInstance();
    dataSource->saveToFile();
    saved=true;
}

void MainWindow::closeEvent(QCloseEvent* event){
    /*if(!saved){
        int ret=QMessageBox::question(this,"是否关闭","数据更改后未保存，可能引发数据丢失");
        if(ret!=QMessageBox::Yes){
            event->ignore();
        }else{
            event->accept();
        }
    }else{
        event->accept();
    }*/

    //TODO remove the remarks to enable exit warning
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
            saved=false;
        }  catch(exception& e) {
            QMessageBox::critical(this,"添加失败",e.what());
        }
    }
}

void MainWindow::on_actionRegistration_triggered()
{
    RegistrationWindow* win=new RegistrationWindow(this);
    win->show();
    this->hide();
}

void MainWindow::on_actionduties_triggered()
{
    mode=MODE_DUTY;
    vector<Duty> duties=DutyService().getAllDuties();

    if(dutyModel==NULL){
        dutyModel=new DutyModel(duties);
    }else{
        dutyModel->setDutiesAndReload(duties);
    }

    ui->dataTable->setModel(dutyModel);
    ui->dataTable->setItemDelegate(dutyDelegate);

    //TODO disable some menus
}

void MainWindow::on_actiondepartments_triggered()
{
    mode=MODE_DEPARTMENT;

    model->setDepartmentsAndReload(departmentService.getAllDepartments());
    ui->dataTable->setModel(model);
    ui->dataTable->setItemDelegate(delegate);

    //TODO disable some menus
}

void MainWindow::on_actiondoctors_triggered()
{
    mode=MDOE_DOCTOR;

    vector<Doctor> doctors=DoctorService().getAllDoctors();
    if(doctorModel==NULL){
        doctorModel=new DoctorModel(doctors);
    }else{
        doctorModel->setDoctorsAndReload(doctors);
    }

    ui->dataTable->setModel(doctorModel);
    ui->dataTable->setItemDelegate(doctorDelegate);
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
