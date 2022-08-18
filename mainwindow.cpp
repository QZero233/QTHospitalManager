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
#include "SelectDepartmentDialog.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set up toolbar
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //Set table not editable
    ui->dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

    //Disable some menus before opening
    ui->actionSave->setVisible(false);
    ui->actionAdd->setVisible(false);
    ui->actionSearchByTel->setVisible(false);
    ui->actionSelectDepartment->setVisible(false);
    ui->actionshowAll->setVisible(false);
    ui->actiongetTodayAppointments->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dataTable_customContextMenuRequested(QPoint pos){
    QModelIndex index=ui->dataTable->indexAt(pos);

    if(index.isValid()){
        contextMenuSelectedIndex=index.row();
        //contextMenuSelectedId=index.sibling(index.row(),0).data().toInt();
        tableMenu->exec(QCursor::pos());
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
    ShowAppointmentsDialog dialog(id);
    dialog.exec();
    model->reloadFromDataSource();
    saved=false;
}

void MainWindow::on_actionOpen_triggered()
{
    //Select file
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString fileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    //Init data source
    DataSource* dataSource=DataSource::getInstance();
    dataSource->setStorageFilePath(fileName.toStdString());
    dataSource->loadFromFile();


    //Generate test data
    /*    Department department1(1,"发热科",996,0*60*60*1000,23*60*60*1000,10,"校医院","88888888");
        Department department2(5,"呼吸科",888,10*60*60*1000,15*60*60*1000,5,"校医院","77777777");
        Department department3(2,"检验科",666,7*60*60*1000,9*60*60*1000+48*60*1000,30,"校医院","66666666");

        departmentService.addDepartment(department1);
        departmentService.addDepartment(department2);
        departmentService.addDepartment(department3);

        //Test appointment add delete update query
        AppointmentService appointmentService;
        for (int i = 1; i <= 10; i++) {
            Appointment appointment;
            appointment.setId(i);
            appointment.setName("张三"+to_string(i));
            appointment.setTelephone("8848" + to_string(i));
            appointment.setGender(Appointment::GENDER_MALE);
            appointment.setAge(i);
            appointment.setAppointmentTime(time(0));
            appointment.setDepartmentId(1);

            appointmentService.addAppointment(appointment);
        }*/

        model=new DepartmentModel(departmentService.getAllDepartments());
        ui->dataTable->setModel(model);

        ui->actionOpen->setVisible(false);
        ui->actionSave->setVisible(true);
        ui->actionAdd->setVisible(true);
        ui->actionSearchByTel->setVisible(true);
        ui->actionSelectDepartment->setVisible(true);
        ui->actiongetTodayAppointments->setVisible(true);

        ui->dataTable->setColumnWidth(4,100);
        ui->dataTable->setColumnWidth(5,100);
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
    int id=index.sibling(index.row(),0).data().toInt();
    if(index.column()==4){
        showAppointmentsDialog(id);
    }else{
        showEditDepartmentDialog(id);
    }
}

void MainWindow::on_actionSave_triggered()
{
    DataSource* dataSource=DataSource::getInstance();
    dataSource->saveToFile();
    saved=true;
}

void MainWindow::closeEvent(QCloseEvent* event){
    if(!saved){
        int ret=QMessageBox::question(this,"是否关闭","数据更改后未保存，可能引发数据丢失");
        if(ret!=QMessageBox::Yes){
            event->ignore();
        }else{
            event->accept();
        }
    }else{
        event->accept();
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


    Department preset(biggestId,"",0,QTime::currentTime().msecsSinceStartOfDay(),
                     QTime::currentTime().msecsSinceStartOfDay(),1,"","" );

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

void MainWindow::on_actionSearchByTel_triggered()
{
    InputTelDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        vector<Appointment> appointments=AppointmentService().
                getAllAppointmentsByTelephone(dialog.getTel().toStdString());

        ShowAppointmentsDialog dialog(appointments);
        dialog.exec();
        model->reloadFromDataSource();
        saved=false;
    }
}

void MainWindow::on_actionshowAll_triggered()
{
    model->setDepartmentsAndReload(departmentService.getAllDepartments());
    ui->actionshowAll->setVisible(false);
}

void MainWindow::on_actionSelectDepartment_triggered()
{
    SelectDepartmentDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        model->setDepartmentsAndReload(dialog.getSatisfiedDepartments());
        ui->actionshowAll->setVisible(true);
    }
}

void MainWindow::on_actiongetTodayAppointments_triggered()
{
    vector<Appointment> appointments=AppointmentService().getAllAppointments();
    vector<Appointment> today;

    QDate dateToday=QDate::currentDate();
    for(Appointment appointment:appointments){
        QDate appointmentDate=QDateTime::fromSecsSinceEpoch(appointment.getAppointmentTime()).date();
        if(appointmentDate==dateToday)
            today.push_back(appointment);
    }

    ShowAppointmentsDialog dialog(today);
    dialog.exec();
    model->reloadFromDataSource();
    saved=false;
}
