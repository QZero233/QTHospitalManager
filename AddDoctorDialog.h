#ifndef ADDDOCTORDIALOG_H
#define ADDDOCTORDIALOG_H

#include <QDialog>

#include "DoctorService.h"

namespace Ui {
class AddDoctorDialog;
}

class AddDoctorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDoctorDialog(QWidget *parent = nullptr);
    ~AddDoctorDialog();

    Doctor getInputDoctor();
private:
    Ui::AddDoctorDialog *ui;
};

#endif // ADDDOCTORDIALOG_H
