#ifndef APPOINTMENTEDITDELEGATE_H
#define APPOINTMENTEDITDELEGATE_H

#include <QItemDelegate>

#include "AppointmentService.h"

class AppointmentEditDelegate : public QItemDelegate
{
public:
    AppointmentEditDelegate(int departmentId,QWidget *parent = NULL):QItemDelegate(parent),
    departmentId(departmentId){}

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private:
    int departmentId;
};

#endif // APPOINTMENTEDITDELEGATE_H
