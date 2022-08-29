#include "SelectDateDialog.h"
#include "ui_SelectDateDialog.h"

SelectDateDialog::SelectDateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDateDialog)
{
    ui->setupUi(this);

    ui->dateEdit_date->setDate(QDate::currentDate());
}

SelectDateDialog::~SelectDateDialog()
{
    delete ui;
}

QDate SelectDateDialog::getDate(){
    return ui->dateEdit_date->date();
}


int SelectDateDialog::getDays(){
    return ui->spinBox_day->value();
}
