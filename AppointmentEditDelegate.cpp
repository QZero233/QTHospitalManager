#include "AppointmentEditDelegate.h"
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>

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
    {
        QDateTimeEdit* dateTimeEdit=new QDateTimeEdit(parent);
        return dateTimeEdit;
    }
    case 6:
        return NULL;
    default:
        return QItemDelegate::createEditor(parent,option,index);
    }

}

void AppointmentEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QVariant data=index.model()->data(index,Qt::EditRole);

    int column=index.column();
    switch(column){
    case 1://Name
    {
        QLineEdit* edit=(QLineEdit*)editor;
        edit->setText(data.toString());
    }
        break;
    case 2://Gender
    {
        QComboBox* box=(QComboBox*)editor;
        if(data.toInt()==Appointment::GENDER_MALE){
            box->setCurrentIndex(0);
        }else{
            box->setCurrentIndex(1);
        }
    }
        break;
    case 3://Age
    {
        QSpinBox* spinBox=(QSpinBox*)editor;
        spinBox->setValue(data.toInt());
    }
        break;
    case 4://Time
    {
        QDateTimeEdit* edit=(QDateTimeEdit*)editor;
        edit->setDateTime(QDateTime::fromSecsSinceEpoch(data.toLongLong()));
    }
        break;
    case 5:
    {
        QLineEdit* edit=(QLineEdit*)editor;
        edit->setText(data.toString());
    }
        break;
    }
}

void AppointmentEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    try{
        int column=index.column();
        switch(column){
        case 1://Name
        {
            QLineEdit* edit=(QLineEdit*)editor;
            model->setData(index,edit->text());
        }
            break;
        case 2://Gender
        {
            QComboBox* box=(QComboBox*)editor;
            int gender=Appointment::GENDER_MALE;
            if(box->currentIndex()==1){
                gender=Appointment::GENDER_FEMALE;
            }
            model->setData(index,gender);
        }
            break;
        case 3://Age
        {
            QSpinBox* spinBox=(QSpinBox*)editor;
            model->setData(index,spinBox->value());
        }
            break;
        case 4://Time
        {
            QDateTimeEdit* edit=(QDateTimeEdit*)editor;
            model->setData(index,edit->dateTime().toSecsSinceEpoch());
        }
            break;
        case 5:
        {
            QLineEdit* edit=(QLineEdit*)editor;
            model->setData(index,edit->text());
        }
            break;
        }
    }catch(exception& e){
        QMessageBox::critical(editor,"修改失败",e.what());
    }
}
