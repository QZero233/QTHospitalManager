#include "DoctorDelegate.h"

#include <QLineEdit>
#include <QComboBox>


QWidget* DoctorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(!index.isValid())
        return NULL;
    switch (index.column()) {
    case 0:
        return NULL;
    case 1:
        return new QLineEdit(parent);
    case 2:
    {
        QComboBox* box=new QComboBox(parent);
        box->addItem("领域专家");
        box->addItem("高级医师");
        box->addItem("实习医师");
        return box;
    }
    case 3:
    {
        QComboBox* box=new QComboBox(parent);
        box->addItems(departmentNames);
        return box;
    }
    }
}

void DoctorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    if(!index.isValid())
        return;

    QVariant data=index.model()->data(index,Qt::EditRole);
    if(index.column()==1){
        //Name
        QLineEdit* edit=(QLineEdit*)editor;
        edit->setText(data.toString());
    }else if(index.column()==2){
        //Position
        QComboBox* edit=(QComboBox*)editor;
        edit->setCurrentIndex(data.toInt());
    }else if(index.column()==3){
        //Department
        QComboBox* edit=(QComboBox*)editor;
        edit->setCurrentIndex(idToIndexMap.value(data.toInt()));
    }
}

void DoctorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    if(!index.isValid())
        return;

    if(index.column()==1){
        //Name
        QLineEdit* edit=(QLineEdit*)editor;
        model->setData(index,edit->text());
    }else if(index.column()==2){
        //Position
        QComboBox* edit=(QComboBox*)editor;
        model->setData(index,edit->currentIndex());
    }else if(index.column()==3){
        QComboBox* edit=(QComboBox*)editor;
        model->setData(index,indexToIdMap.value(edit->currentIndex()));
    }
}
