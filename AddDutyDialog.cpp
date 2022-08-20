#include "AddDutyDialog.h"
#include "ui_AddDutyDialog.h"

AddDutyDialog::AddDutyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDutyDialog)
{
    ui->setupUi(this);
}

AddDutyDialog::~AddDutyDialog()
{
    delete ui;
}
