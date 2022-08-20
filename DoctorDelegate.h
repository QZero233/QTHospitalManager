#ifndef DOCTORDELEGATE_H
#define DOCTORDELEGATE_H

#include <QItemDelegate>

class DoctorDelegate : public QItemDelegate
{
public:
    DoctorDelegate(QWidget *parent = NULL):
        QItemDelegate(parent)
    {

    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // DOCTORDELEGATE_H
