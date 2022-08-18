#include "InputTelDialog.h"
#include "ui_InputTelDialog.h"

InputTelDialog::InputTelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputTelDialog)
{
    ui->setupUi(this);
}

QString InputTelDialog::getTel(){
    return ui->lineEdit_tel->text();
}

InputTelDialog::~InputTelDialog()
{
    delete ui;
}
