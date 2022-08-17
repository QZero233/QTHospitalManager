#include "AddAppointmentDialog.h"
#include "ui_AddAppointmentDialog.h"

#include <QIntValidator>

AddAppointmentDialog::AddAppointmentDialog(int departmentId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAppointmentDialog),
    departmentId(departmentId)
{
    ui->setupUi(this);

    ui->comboBox_gender->addItem("男");
    ui->comboBox_gender->addItem("女");

    ui->lineEdit_id->setValidator(new QIntValidator);

    Department department=DepartmentService().getDepartment(departmentId);
    QTime start=QTime::fromMSecsSinceStartOfDay(department.getAppointmentStartTime());
    QTime end=QTime::fromMSecsSinceStartOfDay(department.getAppointmentEndTime());


    QDateTime time=QDateTime::currentDateTime();
    time.setTime(start);
    ui->dateTimeEdit_time->setDateTime(time);
    ui->dateTimeEdit_time->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit_time->setTimeRange(start,end);
}

AddAppointmentDialog::~AddAppointmentDialog()
{
    delete ui;
}

void AddAppointmentDialog::on_pushButton_clicked()
{
    vector<Appointment> appointments=service.getAllAppointments(departmentId);
    int biggestId=1;
    for(Appointment appointment:appointments){
        if(appointment.getId()>biggestId)
            biggestId=appointment.getId();
    }

    int id=biggestId+1;

    ui->lineEdit_id->setText(QString::number(id));
}

void AddAppointmentDialog::accept(){
    int id=ui->lineEdit_id->text().toInt();
    string name=ui->lineEdit_name->text().toStdString();
    int gender=(ui->comboBox_gender->currentIndex()==0)?Appointment::GENDER_MALE:Appointment::GENDER_FEMALE;
    int age=ui->spinBox_age->value();
    string tel=ui->lineEdit_tel->text().toStdString();
    long time=ui->dateTimeEdit_time->dateTime().toSecsSinceEpoch();

    currentStored.setId(id);
    currentStored.setName(name);
    currentStored.setGender(gender);
    currentStored.setAge(age);
    currentStored.setTelephone(tel);
    currentStored.setAppointmentTime(time);

    QDialog::accept();
}
