#include "LoginWindow.h"
#include "ui_LoginWindow.h"

#include "mainwindow.h"
#include "RegistrationWindow.h"

#include <QMessageBox>
#include "AppointmentService.h"

void addTestData();

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);

    //Init data source
    DataSource* dataSource=DataSource::getInstance();
    dataSource->setStorageFilePath("record.txt");
    dataSource->loadFromFile();
    //addTestData();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void addTestData(){
    //Add 5 departments
    DepartmentService departmentService;
    for(int i=1;i<=5;i++){
        Department department(i,"科室"+to_string(i),"地址1"+to_string(i),"电话1"+to_string(i));
        departmentService.addDepartment(department);
    }

    //Add 10 doctors
    DoctorService doctorService;
    for(int i=1;i<=10;i++){
        int position=Doctor::POSITION_PRACTICE;
        if(i%3==1)
            position=Doctor::POSITION_SENIOR;
        else if(i%3==2)
            position=Doctor::POSITION_JUNIOR;

        Doctor doctor(i,"医生"+to_string(i),position,(i%5+1));
        doctorService.addDoctor(doctor);
    }

    //Add 6 duties
    DutyService dutyService;
    long long today=QDate::currentDate().toJulianDay();
    int capacity=1;
    dutyService.addDuty(Duty(1,1,Duty::TIME_PERIOD_AM,today,capacity));
    dutyService.addDuty(Duty(2,1,Duty::TIME_PERIOD_PM,today,capacity));
    dutyService.addDuty(Duty(3,3,Duty::TIME_PERIOD_AM,today,capacity));
    dutyService.addDuty(Duty(4,4,Duty::TIME_PERIOD_PM,today,capacity));
    dutyService.addDuty(Duty(5,5,Duty::TIME_PERIOD_AM,today,capacity));
    dutyService.addDuty(Duty(6,6,Duty::TIME_PERIOD_PM,today,capacity));

    //Add 10 appointments
    AppointmentService appointmentService;
    appointmentService.addAppointment(Appointment(1,"预约1","电话1",0,18,2,TIME_PERIOD_AM_1));
    appointmentService.addAppointment(Appointment(2,"预约2","电话2",1,18,5,TIME_PERIOD_AM_1));
}

void LoginWindow::on_pushButton_clicked()
{
    //Admin
    if(ui->lineEdit_pwd->text()==""){
        //QMessageBox::information(this,"成功","欢迎登陆");

        MainWindow* win=new MainWindow;
        win->show();
        close();
    }else{
        QMessageBox::critical(this,"错误","密码错误");
    }
}

void LoginWindow::on_pushButton_2_clicked()
{
    //Patient
    //QMessageBox::information(this,"成功","欢迎登陆");

    RegistrationWindow* win=new RegistrationWindow;
    win->show();
    close();
}
