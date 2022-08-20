#ifndef DUTYDELEGATE_H
#define DUTYDELEGATE_H

#include <QItemDelegate>

class DutyDelegate : public QItemDelegate
{
public:
    DutyDelegate(QWidget *parent = NULL):
        QItemDelegate(parent)
    {

    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DUTYDELEGATE_H
