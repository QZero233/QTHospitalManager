#include "ShowAppointmentsDialog.h"
#include "ui_ShowAppointmentsDialog.h"

#include "ReadOnlyDelegate.h"

#include <QStringList>
#include <QAction>
#include <QMessageBox>

#include <QMenu>
#include <QAction>

#include "TimeUtils.h"

ShowAppointmentsDialog::ShowAppointmentsDialog(const vector<Appointment>& appointments,
                                               QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ShowAppointmentsDialog)
{
    ui->setupUi(this);
    model=new AppointmentModel(appointments);

    ui->dataTable->setModel(model);
    ui->dataTable->setItemDelegate(new ReadOnlyDelegate());

    ui->dataTable->setColumnWidth(4,120);
}

void ShowAppointmentsDialog::setAllowDelete(){
    //Add context menu
    tableMenu=new QMenu(ui->dataTable);
    deleteAction=new QAction("取消预约",ui->dataTable);
    tableMenu->addAction(deleteAction);

    ui->dataTable->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->dataTable,SIGNAL(customContextMenuRequested(QPoint)),this,
                SLOT(dataTable_customContextMenuRequested(QPoint)));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(dataTable_delete_triggered()));
}

void ShowAppointmentsDialog::dataTable_delete_triggered(){
    QMessageBox box;
    box.setText("是否取消预约");
    box.setInformativeText("此操作不可逆！");
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Ok);
    int ret=box.exec();
    if(ret==QMessageBox::Ok){
        model->deleteAppoinment(contextMenuSelectedIndex);
    }
}

void ShowAppointmentsDialog::dataTable_customContextMenuRequested(QPoint pos){
    QModelIndex index=ui->dataTable->indexAt(pos);

        if(index.isValid()){
            contextMenuSelectedIndex=index.row();
            tableMenu->exec(QCursor::pos());
        }
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
