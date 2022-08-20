#ifndef DEPARTMENTDELEGATE_H
#define DEPARTMENTDELEGATE_H

#include <QItemDelegate>

class DepartmentDelegate : public QItemDelegate
{
public:
    DepartmentDelegate(QWidget *parent = NULL):
        QItemDelegate(parent)
    {

    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DEPARTMENTDELEGATE_H
