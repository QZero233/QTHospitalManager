#ifndef ADDDUTYDIALOG_H
#define ADDDUTYDIALOG_H

#include <QDialog>

namespace Ui {
class AddDutyDialog;
}

class AddDutyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDutyDialog(QWidget *parent = nullptr);
    ~AddDutyDialog();

private:
    Ui::AddDutyDialog *ui;
};

#endif // ADDDUTYDIALOG_H
