#include "TimeDutyDelegate.h"

QWidget* TimeDutyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    return NULL;
}

void TimeDutyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(!index.isValid())
        return;
    QStyleOptionViewItem so = option;

    if(index.column()==2){
        bool full=index.model()->data(index,Qt::EditRole).toBool();
        if(full){
            so.palette.setColor(QPalette::Text,QColor(255,0,0));
        }else{
            so.palette.setColor(QPalette::Text,QColor(0,139,0));
        }
    }

    QItemDelegate::paint(painter,so,index);
}
