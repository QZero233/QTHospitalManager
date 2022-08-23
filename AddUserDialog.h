#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

#include "User.h"

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(bool adminMode,QWidget *parent = nullptr);
    ~AddUserDialog();

    User getInputUser();

private:
    Ui::AddUserDialog *ui;

    bool adminMode;
};

#endif // ADDUSERDIALOG_H
