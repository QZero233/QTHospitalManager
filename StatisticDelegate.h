#ifndef STATISTICDELEGATE_H
#define STATISTICDELEGATE_H

#include <QItemDelegate>

class StatisticDelegate : public QItemDelegate
{
public:
    StatisticDelegate(QWidget *parent = NULL):
        QItemDelegate(parent)
    {

    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif // STATISTICDELEGATE_H
