#ifndef ADDDUTYDIALOG_H
#define ADDDUTYDIALOG_H

#include <QDialog>

#include "DoctorService.h"

#include "Duty.h"

namespace Ui {
class AddDutyDialog;
}

class AddDutyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDutyDialog(QWidget *parent = nullptr);
    ~AddDutyDialog();

    Duty getInputDuty();
private:
    Ui::AddDutyDialog *ui;
    vector<Doctor> doctors;
};

#endif // ADDDUTYDIALOG_H
