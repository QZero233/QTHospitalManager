#include "AppointmentEditDelegate.h"
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QStandardItem>
#include <QStandardItemModel>

#include "TimeUtils.h"

QWidget* AppointmentEditDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const{
    int column=index.column();
    switch(column){
    case 0:
        return NULL;
    case 2://Gender
    {
        QComboBox* box=new QComboBox(parent);
        box->addItem("男");
        box->addItem("女");
        return box;
    }
    case 3://Age
    {
        QSpinBox* spinBox=new QSpinBox(parent);
        spinBox->setMinimum(1);
        return spinBox;
    }
    case 4://Appointment time
        return new QDateTimeEdit(parent);
    default:
        return QItemDelegate::createEditor(parent,option,index);
    }

}

void AppointmentEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    AppointmentService service;

    int id=index.sibling(index.row(),0).data().toInt();
    Appointment appointment=service.getAppointment(departmentId,id);


    int column=index.column();
    switch(column){
    case 1://Name
    {
        QLineEdit* edit=(QLineEdit*)editor;
        edit->setText(appointment.getName().c_str());
    }
        break;
    case 2://Gender
    {
        QComboBox* box=(QComboBox*)editor;
        if(appointment.getGender()==Appointment::GENDER_MALE){
            box->setCurrentIndex(0);
        }else{
            box->setCurrentIndex(1);
        }
    }
        break;
    case 3://Age
    {
        QSpinBox* spinBox=(QSpinBox*)editor;
        spinBox->setValue(appointment.getAge());
    }
        break;
    case 4://Time
    {
        QDateTimeEdit* edit=(QDateTimeEdit*)editor;
        edit->setDateTime(QDateTime::fromSecsSinceEpoch(appointment.getAppointmentTime()));
    }
        break;
    case 5:
    {
        QLineEdit* edit=(QLineEdit*)editor;
        edit->setText(appointment.getTelephone().c_str());
    }
        break;
    }
}

void AppointmentEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    AppointmentService service;

    int id=index.sibling(index.row(),0).data().toInt();
    Appointment appointment=service.getAppointment(departmentId,id);

    try{
        int column=index.column();
        switch(column){
        case 1://Name
        {
            QLineEdit* edit=(QLineEdit*)editor;
            appointment.setName(edit->text().toStdString());
        }
            break;
        case 2://Gender
        {
            QComboBox* box=(QComboBox*)editor;
            if(box->currentIndex()==0){
                appointment.setGender(Appointment::GENDER_MALE);
            }else{
                appointment.setGender(Appointment::GENDER_FEMALE);
            }
        }
            break;
        case 3://Age
        {
            QSpinBox* spinBox=(QSpinBox*)editor;
            appointment.setAge(spinBox->value());
        }
            break;
        case 4://Time
        {
            QDateTimeEdit* edit=(QDateTimeEdit*)editor;
            appointment.setAppointmentTime(edit->dateTime().toSecsSinceEpoch());
        }
            break;
        case 5:
        {
            QLineEdit* edit=(QLineEdit*)editor;
            appointment.setTelephone(edit->text().toStdString());
        }
            break;
        }

        service.updateAppointment(departmentId,appointment);
        //Update model
        switch(column){
        case 1:
            model->setData(index,QVariant(appointment.getName().c_str()));
            break;
        case 2:
            model->setData(index,QVariant(appointment.getGender()==Appointment::GENDER_MALE?"男":"女"));
            break;
        case 3:
            model->setData(index,QVariant(appointment.getAge()));
            break;
        case 4:
            model->setData(index,QVariant(TimeUtils::formatTimeStamp(appointment.getAppointmentTime())));
            break;
        case 5:
            model->setData(index,QVariant(appointment.getTelephone().c_str()));
            break;
        }
    }catch(...){

    }
}
