#include "StatisticDelegate.h"

QWidget* StatisticDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    return NULL;
}

void StatisticDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(!index.isValid())
        return;
    QStyleOptionViewItem so = option;
    if(index.column()!=0){
        double percentage=index.model()->data(index,Qt::EditRole).toDouble();

        if(percentage<0.5){
            so.palette.setColor(QPalette::Text,QColor(0,139,0));
        }else if(percentage==1){
            so.palette.setColor(QPalette::Text,QColor(255,0,0));
        }else{
            so.palette.setColor(QPalette::Text,QColor(255,193,37));
        }
    }
    QItemDelegate::paint(painter,so,index);
}
