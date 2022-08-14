#ifndef DEPARTMENTEDITDIALOG_H
#define DEPARTMENTEDITDIALOG_H

#include <QDialog>

#include "DepartmentService.h"

namespace Ui {
class DepartmentEditDIalog;
}

class DepartmentEditDIalog : public QDialog
{
    Q_OBJECT

public:
    explicit DepartmentEditDIalog(QWidget *parent = nullptr);
    ~DepartmentEditDIalog();

    void setPreset(const Department& preset);
    void setIdEditable(bool idEditable);
    Department getStored();
private:
    Ui::DepartmentEditDIalog *ui;

    Department currentStored;

protected:
    void accept() override;
};

#endif // DEPARTMENTEDITDIALOG_H
