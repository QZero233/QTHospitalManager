#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include <iostream>

#include <QStringList>
#include <QStandardItem>

#include "AppointmentService.h"

#include "TimeUtils.h"

#include "departmenteditdialog.h"
#include "ShowAppointmentsDialog.h"

using namespace std;
//TODO try delegate
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model=new QStandardItemModel();
    ui->dataTable->setModel(model);
    //Set table not editable
    ui->dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Add right-click menu
    tableMenu=new QMenu(ui->dataTable);
    QAction* editAction=new QAction("编辑",ui->dataTable);
    QAction* deleteAction=new QAction("删除",ui->dataTable);
    QAction* appointmentsAction=new QAction("查看预约",ui->dataTable);
    tableMenu->addAction(editAction);
    tableMenu->addAction(deleteAction);
    tableMenu->addAction(appointmentsAction);
    ui->dataTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->dataTable,SIGNAL(customContextMenuRequested(QPoint)),this,
            SLOT(dataTable_customContextMenuRequested(QPoint)));
    connect(editAction,SIGNAL(triggered()),this,SLOT(dataTable_edit_triggered()));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(dataTable_delete_triggered()));
    connect(appointmentsAction,SIGNAL(triggered()),this,SLOT(dataTable_appointments_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dataTable_customContextMenuRequested(QPoint pos){
    QModelIndex index=ui->dataTable->indexAt(pos);

    if(index.isValid()){
        contextMenuSelectedId=index.sibling(index.row(),0).data().toInt();
        tableMenu->exec(QCursor::pos());
    }
}

void MainWindow::dataTable_edit_triggered(){
    int id=contextMenuSelectedId;
    if(id<0)
        return;

    showEditDepartmentDialog(id);
}

void MainWindow::dataTable_delete_triggered(){
    //TODO confirm dialog
}

void MainWindow::dataTable_appointments_triggered(){
    showAppointmentsDialog(contextMenuSelectedId);
}

void MainWindow::showEditDepartmentDialog(int id){
    Department department=departmentService.getDepartment(id);

    DepartmentEditDIalog dialog;
    dialog.setIdEditable(false);
    dialog.setPreset(department);
    int ret=dialog.exec();
    if(ret==QDialog::Accepted){
        //Update
        departmentService.updateDepartment(dialog.getStored());
        //Flush UI
        displayDepartmentData();
    }
}

void MainWindow::showAppointmentsDialog(int id){
    ShowAppointmentsDialog dialog(id);
    dialog.exec();
    displayDepartmentData();
}

void MainWindow::displayDepartmentData(){
    model->clear();

    //Set header
    QStringList list;
    list.append("门诊编号");
    list.append("门诊名称");
    list.append("值班医生工号");
    list.append("每日接诊时间");
    list.append("剩余容量/总容量");
    list.append("门诊地址");
    list.append("联系电话");
    model->setHorizontalHeaderLabels(list);

    //Fill data
    vector<Department> departments=departmentService.getAllDepartments();

    QStandardItem* item;
    for(int i=0;i<departments.size();i++){
        Department department=departments[i];

        item=new QStandardItem(QString("%1").arg(department.getId()));
        model->setItem(i,0,item);

        item=new QStandardItem(QString(department.getName().c_str()));
        model->setItem(i,1,item);

        item=new QStandardItem(QString("%1").arg(department.getIdOfDutyDoctor()));
        model->setItem(i,2,item);

        item=new QStandardItem(QString("%1-%2").arg(
                                   TimeUtils::formatTimeFromStartOfDayByQT(department.getAppointmentStartTime()),
                                   TimeUtils::formatTimeFromStartOfDayByQT(department.getAppointmentEndTime())));
        model->setItem(i,3,item);

        item=new QStandardItem(QString("%1/%2").arg(QString::number(department.getAppointmentsPtr()->size())
                                                    ,QString::number(department.getCapacity())));
        model->setItem(i,4,item);

        item=new QStandardItem(QString(department.getAddress().c_str()));
        model->setItem(i,5,item);

        item=new QStandardItem(QString(department.getTelephone().c_str()));
        model->setItem(i,6,item);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    //Generate test data
        Department department1(1,"发热科",996,3*60*60*1000,5*60*60*1000,10,"校医院","88888888");
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

            appointmentService.addAppointment(1, appointment);
        }
    displayDepartmentData();
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
