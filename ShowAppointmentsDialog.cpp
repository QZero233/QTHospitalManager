#include "ShowAppointmentsDialog.h"
#include "ui_ShowAppointmentsDialog.h"

#include "AppointmentEditDelegate.h"
#include "AddAppointmentDialog.h"

#include <QStringList>
#include <QAction>
#include <QMessageBox>

#include "TimeUtils.h"

ShowAppointmentsDialog::ShowAppointmentsDialog(const vector<Appointment>& appointments,
                                               QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ShowAppointmentsDialog)
{
    ui->setupUi(this);
    model=new AppointmentModel(appointments);
    initUI();
    addAction->setEnabled(false);
}

ShowAppointmentsDialog::ShowAppointmentsDialog(int departmentId,
                                               QWidget *parent):
  QDialog(parent),
  ui(new Ui::ShowAppointmentsDialog),
  departmentId(departmentId)
{
    ui->setupUi(this);
    model=new AppointmentModel(departmentId);
    initUI();
}

void ShowAppointmentsDialog::initUI(){
    ui->dataTable->setModel(model);

    AppointmentEditDelegate* delegate=new AppointmentEditDelegate();
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

    ui->dataTable->setColumnWidth(4,100);
    ui->dataTable->setColumnWidth(5,100);
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

        contextMenuSelectedIndex=index.row();
        tableMenu->exec(QCursor::pos());
    }else{
        //Show add menu in blank places
        deleteAction->setVisible(false);
        addAction->setVisible(true);

        contextMenuSelectedIndex=-1;
        tableMenu->exec(QCursor::pos());
    }
}

void ShowAppointmentsDialog::dataTable_delete_triggered(){
    //Show confirm dialog
    Appointment appointment=model->getAppointmentByIndex(contextMenuSelectedIndex);
    QMessageBox box;
    box.setText(("是否删除患者 "+appointment.getName()+" 的预约记录？").c_str());
    box.setInformativeText("此操作不可逆！");
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Ok);
    int ret=box.exec();
    if(ret==QMessageBox::Ok){
        //Delete
        model->deleteAppoinment(contextMenuSelectedIndex);
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
            model->addAppointment(dialog.getCurrentStored());
        }catch(exception& e){
            QMessageBox::critical(this,"添加失败",e.what());
        }
    }
}
