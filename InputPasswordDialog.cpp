#include "InputPasswordDialog.h"
#include "ui_InputPasswordDialog.h"


InputPasswordDialog::InputPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPasswordDialog)
{
    ui->setupUi(this);

    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
}

QString InputPasswordDialog::getPwd(){
    return ui->lineEdit_pwd->text();
}

InputPasswordDialog::~InputPasswordDialog()
{
    delete ui;
}
