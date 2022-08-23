#ifndef SHOWTIMEDUTYDIALOG_H
#define SHOWTIMEDUTYDIALOG_H

#include <QDialog>

#include "User.h"

#include "TimeDutyModel.h"

namespace Ui {
class ShowTimeDutyDialog;
}

class ShowTimeDutyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTimeDutyDialog(User user,vector<Duty> duties,QWidget *parent = nullptr);
    ~ShowTimeDutyDialog();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_dataTable_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowTimeDutyDialog *ui;

    User user;

    TimeDutyModel* model;
};

#endif // SHOWTIMEDUTYDIALOG_H
