#include "departmenteditdialog.h"
#include "ui_departmenteditdialog.h"

#include <QIntValidator>

#include <iostream>

DepartmentEditDIalog::DepartmentEditDIalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepartmentEditDIalog)
{
    ui->setupUi(this);

    ui->lineEdit_id->setValidator(new QIntValidator());
}

DepartmentEditDIalog::~DepartmentEditDIalog()
{
    delete ui;
}

void DepartmentEditDIalog::setPreset(const Department& preset){
    currentStored=preset;
    ui->lineEdit_id->setText(QString::number(preset.getId()));
    ui->lineEdit_name->setText(QString(preset.getName().c_str()));
    ui->lineEdit_tel->setText(QString(preset.getTelephone().c_str()));
    ui->lineEdit_address->setText(QString(preset.getAddress().c_str()));
}
void DepartmentEditDIalog::setIdEditable(bool idEditable){
    ui->lineEdit_id->setEnabled(idEditable);
}
Department DepartmentEditDIalog::getStored(){
    return currentStored;
}

void DepartmentEditDIalog::accept(){
    currentStored.setId(ui->lineEdit_id->text().toInt());
    currentStored.setName(ui->lineEdit_name->text().toStdString());
    currentStored.setTelephone(ui->lineEdit_tel->text().toStdString());
    currentStored.setAddress(ui->lineEdit_address->text().toStdString());

    QDialog::accept();
}
