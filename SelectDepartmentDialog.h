#ifndef SELECTDEPARTMENTDIALOG_H
#define SELECTDEPARTMENTDIALOG_H

#include <QDialog>

#include "DepartmentService.h"

namespace Ui {
class SelectDepartmentDialog;
}

class SelectDepartmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDepartmentDialog(QWidget *parent = nullptr);
    ~SelectDepartmentDialog();

    vector<Department> getSatisfiedDepartments();
private slots:
    void on_checkBox_time_stateChanged(int arg1);

    void on_checkBox_id_stateChanged(int arg1);

    void on_checkBox_capacity_stateChanged(int arg1);

private:
    Ui::SelectDepartmentDialog *ui;

    bool enableTime=true;
    bool enableId=true;
    bool enableCapacity=true;
};

#endif // SELECTDEPARTMENTDIALOG_H
