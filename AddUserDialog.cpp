#include "AddUserDialog.h"
#include "ui_AddUserDialog.h"

AddUserDialog::AddUserDialog(bool adminMode,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog),
    adminMode(adminMode)
{
    ui->setupUi(this);

    ui->comboBox_group->addItem("管理员");
    ui->comboBox_group->addItem("患者");

    ui->comboBox_gender->addItem("男");
    ui->comboBox_gender->addItem("女");

    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    if(!adminMode){
        ui->comboBox_group->setEnabled(false);
        ui->comboBox_group->setCurrentIndex(1);
    }
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}


User AddUserDialog::getInputUser(){
    User user;

    user.setUsername(ui->lineEdit_username->text().toStdString());
    user.setPassword(ui->lineEdit_password->text().toStdString());

    user.setName(ui->lineEdit_name->text().toStdString());
    user.setTelephone(ui->lineEdit_tel->text().toStdString());
    user.setAge(ui->spinBox_age->value());
    user.setGender(ui->comboBox_gender->currentIndex()==0?User::GENDER_MALE:User::GENDER_FEMALE);

    if(adminMode){
        user.setGroup(ui->comboBox_group->currentIndex()==0?User::GROUP_ADMIN:User::GROUP_PATIENT);
    }else{
        user.setGroup(User::GROUP_PATIENT);
    }

    return user;
}
