#ifndef USERDELEGATE_H
#define USERDELEGATE_H

#include <QItemDelegate>
#include <QMap>


#include "DepartmentService.h"

class UserDelegate : public QItemDelegate
{
public:
    UserDelegate(QWidget *parent = NULL):
        QItemDelegate(parent)
    {
    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
private:

};
#endif // USERDELEGATE_H
