#include "DoctorStatisticDialog.h"
#include "ui_DoctorStatisticDialog.h"

#include "DoctorService.h"

#include "DoctorStatisticModel.h"

#include "StatisticDelegate.h"

DoctorStatisticDialog::DoctorStatisticDialog(int departmentId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoctorStatisticDialog),
    departmentId(departmentId)
{
    ui->setupUi(this);

    vector<Doctor> doctors=DoctorService().getAllByDepartmentId(departmentId);
    ui->dataTable->setModel(new DoctorStatisticModel(doctors));
    ui->dataTable->setItemDelegate(new StatisticDelegate());

    ui->dataTable->setColumnWidth(1,100);
    ui->dataTable->setColumnWidth(2,100);
    ui->dataTable->setColumnWidth(3,100);
}

DoctorStatisticDialog::~DoctorStatisticDialog()
{
    delete ui;
}

void DoctorStatisticDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->dataTable->setGeometry(5,5,x*0.99,y*0.99);
}
