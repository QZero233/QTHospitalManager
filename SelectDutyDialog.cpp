#include "SelectDutyDialog.h"
#include "ui_SelectDutyDialog.h"

SelectDutyDialog::SelectDutyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDutyDialog)
{
    ui->setupUi(this);
}

SelectDutyDialog::~SelectDutyDialog()
{
    delete ui;
}
