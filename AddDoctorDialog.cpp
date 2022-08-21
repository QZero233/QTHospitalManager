#include "AddDoctorDialog.h"
#include "ui_AddDoctorDialog.h"



AddDoctorDialog::AddDoctorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDoctorDialog)
{
    ui->setupUi(this);

    ui->comboBox_position->addItem("领域专家");
    ui->comboBox_position->addItem("高级医师");
    ui->comboBox_position->addItem("实习医师");

    departments=DepartmentService().getAllDepartments();
    for(Department department:departments){
        ui->comboBox_department->addItem(department.getName().c_str());
    }
}

AddDoctorDialog::~AddDoctorDialog()
{
    delete ui;
}

Doctor AddDoctorDialog::getInputDoctor(){
    Doctor doctor;
    doctor.setId(DoctorService().getUniqueId());
    doctor.setName(ui->lineEdit_name->text().toStdString());
    doctor.setPosition(ui->comboBox_position->currentIndex());

    Department department=departments[ui->comboBox_department->currentIndex()];
    doctor.setDepartmentId(department.getId());

    return doctor;
}
