#ifndef SELECTDUTYDIALOG_H
#define SELECTDUTYDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDutyDialog;
}

class SelectDutyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDutyDialog(QWidget *parent = nullptr);
    ~SelectDutyDialog();

private:
    Ui::SelectDutyDialog *ui;
};

#endif // SELECTDUTYDIALOG_H
