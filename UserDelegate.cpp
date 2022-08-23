#include "UserDelegate.h"

#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>


QWidget* UserDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(!index.isValid())
        return NULL;
    switch (index.column()) {
    case 0:
        return NULL;
    case 1:
    {
        QLineEdit* edit=new QLineEdit(parent);
        edit->setEchoMode(QLineEdit::Password);
        return edit;
    }
    case 2:
    {
        QComboBox* box=new QComboBox(parent);

        box->addItem("管理员");
        box->addItem("患者");

        return box;
    }
    case 3:
        return new QLineEdit(parent);
    case 4:
        return new QLineEdit(parent);
    case 5:
    {
        QComboBox* box=new QComboBox(parent);

        box->addItem("男");
        box->addItem("女");

        return box;
    }
    case 6:
    {
        QSpinBox* box=new QSpinBox(parent);
        box->setMinimum(1);
        box->setMaximum(114514);

        return box;
    }
    default:
        return NULL;
    }
}

void UserDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    if(!index.isValid())
        return;

    QVariant data=index.model()->data(index,Qt::EditRole);
    switch(index.column()){
    case 2:
        //Group
    {
        QComboBox* box=(QComboBox*)editor;
        box->setCurrentIndex(data.toInt()==User::GROUP_ADMIN?0:1);
    }
        break;
    case 3:
    case 4:
        //Name and Tel
    {
        QLineEdit* edit=(QLineEdit*)editor;
        edit->setText(data.toString());
    }
        break;
    case 5:
        //Gender
    {
        QComboBox* box=(QComboBox*)editor;
        box->setCurrentIndex(data.toInt()==User::GENDER_MALE?0:1);
    }
        break;
    case 6:
        //Age
    {
        QSpinBox* box=(QSpinBox*)editor;
        box->setValue(data.toInt());
    }
        break;

    }
}

void UserDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    if(!index.isValid())
        return;

    switch(index.column()){
    case 1:
    case 3:
    case 4:
        //Password, name, tel

    {
        QLineEdit* edit=(QLineEdit*)editor;
        //When password is empty, do not change it
        if(index.column()==1 && edit->text()=="")
            break;
        model->setData(index,edit->text());
    }
        break;
    case 2:
        //Group
    {
        QComboBox* box=(QComboBox*)editor;
        model->setData(index,box->currentIndex()==0?User::GROUP_ADMIN:User::GROUP_PATIENT);
    }
        break;
    case 5:
        //Gender
    {
        QComboBox* box=(QComboBox*)editor;
        model->setData(index,box->currentIndex()==0?User::GENDER_MALE:User::GENDER_FEMALE);
    }
        break;
    case 6:
        //Age
    {
        QSpinBox* box=(QSpinBox*)editor;
        model->setData(index,box->value());
    }
        return;

    }
}
