#ifndef SHOWTIMEDUTYDIALOG_H
#define SHOWTIMEDUTYDIALOG_H

#include <QDialog>

#include "TimeDutyModel.h"

namespace Ui {
class ShowTimeDutyDialog;
}

class ShowTimeDutyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTimeDutyDialog(User user,int departmentId,vector<Duty> duties,QWidget *parent = nullptr);
    ~ShowTimeDutyDialog();

private slots:
    void on_dataTable_doubleClicked(const QModelIndex &index);

    void on_dateEdit_date_userDateChanged(const QDate &date);

private:
    Ui::ShowTimeDutyDialog *ui;

    User user;

    int departmentId;

    TimeDutyModel* model;
};

#endif // SHOWTIMEDUTYDIALOG_H
