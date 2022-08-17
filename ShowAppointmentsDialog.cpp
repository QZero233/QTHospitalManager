#include "ShowAppointmentsDialog.h"
#include "ui_ShowAppointmentsDialog.h"

#include "AppointmentEditDelegate.h"
#include "AddAppointmentDialog.h"

#include <QStringList>
#include <QAction>
#include <QMessageBox>

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
    ui->dataTable->setItemDelegate(delegate);

    //Set up table context menu
    tableMenu=new QMenu(ui->dataTable);
    deleteAction=new QAction("删除",ui->dataTable);
    addAction=new QAction("添加",ui->dataTable);
    tableMenu->addAction(deleteAction);
    tableMenu->addAction(addAction);
    ui->dataTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->dataTable,SIGNAL(customContextMenuRequested(QPoint)),this,
            SLOT(dataTable_customContextMenuRequested(QPoint)));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(dataTable_delete_triggered()));
    connect(addAction,SIGNAL(triggered()),this,SLOT(dataTable_add_triggered()));

    displayAppointments();

}

ShowAppointmentsDialog::~ShowAppointmentsDialog()
{
    delete ui;
}

void ShowAppointmentsDialog::dataTable_customContextMenuRequested(QPoint pos){
    QModelIndex index=ui->dataTable->indexAt(pos);

    if(index.isValid()){
        deleteAction->setVisible(true);
        addAction->setVisible(false);

        contextMenuSelectedId=index.sibling(index.row(),0).data().toInt();
        tableMenu->exec(QCursor::pos());
    }else{
        //Show add menu in blank places
        deleteAction->setVisible(false);
        addAction->setVisible(true);

        contextMenuSelectedId=-1;
        tableMenu->exec(QCursor::pos());
    }
}

void ShowAppointmentsDialog::dataTable_delete_triggered(){
    //Show confirm dialog
    Appointment appointment=service.getAppointment(departmentId,contextMenuSelectedId);
    QMessageBox box;
    box.setText(("是否删除患者 "+appointment.getName()+" 的预约记录？").c_str());
    box.setInformativeText("此操作不可逆！");
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Ok);
    int ret=box.exec();
    if(ret==QMessageBox::Ok){
        //Delete
        service.deleteAppointment(departmentId,contextMenuSelectedId);
        displayAppointments();
    }
}

void ShowAppointmentsDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->dataTable->setGeometry(5,5,x*0.99,y*0.99);
}

void ShowAppointmentsDialog::dataTable_add_triggered(){
    AddAppointmentDialog dialog(departmentId);
    int ret=dialog.exec();
    if(ret==QDialog::Accepted){
        try{
            //Add
            service.addAppointment(departmentId,dialog.getCurrentStored());
            displayAppointments();
        }catch(runtime_error& e){
            QMessageBox::critical(this,"添加失败",e.what());
        }
    }
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
