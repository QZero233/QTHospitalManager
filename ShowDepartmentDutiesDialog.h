#ifndef SHOWDEPARTMENTDUTIESDIALOG_H
#define SHOWDEPARTMENTDUTIESDIALOG_H

#include <QDialog>

#include "DutyModel.h"
#include "TimeDutyModel.h"

namespace Ui {
class ShowDepartmentDutiesDialog;
}

class ShowDepartmentDutiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowDepartmentDutiesDialog(int timePeriod,User user,vector<Duty> duties,QWidget *parent = nullptr);
    ~ShowDepartmentDutiesDialog();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_dataTable_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowDepartmentDutiesDialog *ui;

    DutyModel* model;

    User user;

    int timePeriod;
    bool timeFixed=false;
};

#endif // SHOWDEPARTMENTDUTIESDIALOG_H
