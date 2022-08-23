#include "ShowTimeDutyDialog.h"
#include "ui_ShowTimeDutyDialog.h"

#include "TimeDutyDelegate.h"

#include "ShowDepartmentDutiesDialog.h"

#include <QMessageBox>

ShowTimeDutyDialog::ShowTimeDutyDialog(User user,vector<Duty> duties,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowTimeDutyDialog),
    user(user)
{
    ui->setupUi(this);

    model=new TimeDutyModel(duties,QDate::currentDate(),5);

    ui->dataTable->setModel(model);
    ui->dataTable->setItemDelegate(new TimeDutyDelegate());
}

ShowTimeDutyDialog::~ShowTimeDutyDialog()
{
    delete ui;
}

void ShowTimeDutyDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->dataTable->setGeometry(5,5,x*0.99,y*0.99);
}

void ShowTimeDutyDialog::on_dataTable_doubleClicked(const QModelIndex &index)
{
    if(model->checkIfFull(index)){
        QMessageBox::critical(this,"错误","该时段预约已满，不再接受预约");
        return;
    }

    vector<Duty> duties=model->getDutiesByIndex(index);
    int timePeriod=model->getTimePeriodByIndex(index);

    ShowDepartmentDutiesDialog dialog(timePeriod,user,duties);
    dialog.exec();
}
