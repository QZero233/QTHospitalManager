#ifndef TIMEDUTYDELEGATE_H
#define TIMEDUTYDELEGATE_H

#include <QItemDelegate>

class TimeDutyDelegate : public QItemDelegate
{
public:
    TimeDutyDelegate(QWidget *parent = NULL):
        QItemDelegate(parent)
    {

    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TIMEDUTYDELEGATE_H
