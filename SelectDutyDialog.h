#ifndef SELECTDUTYDIALOG_H
#define SELECTDUTYDIALOG_H

#include <QDialog>

#include "DutyService.h"
#include "DepartmentService.h"
#include "DoctorService.h"

namespace Ui {
class SelectDutyDialog;
}

class SelectDutyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDutyDialog(QWidget *parent = nullptr);
    ~SelectDutyDialog();

    vector<Duty> getSatsfitedDuties();

private slots:
    void on_checkBox_no_time_stateChanged(int arg1);

    void on_comboBox_department_activated(int index);

private:
    Ui::SelectDutyDialog *ui;

    vector<Department> departments;
    vector<Doctor> doctors;
};

#endif // SELECTDUTYDIALOG_H
