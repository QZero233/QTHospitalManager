#ifndef DOCTORSTATISTICDIALOG_H
#define DOCTORSTATISTICDIALOG_H

#include <QDialog>

namespace Ui {
class DoctorStatisticDialog;
}

class DoctorStatisticDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorStatisticDialog(int departmentId,QWidget *parent = nullptr);
    ~DoctorStatisticDialog();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::DoctorStatisticDialog *ui;

    int departmentId;
};

#endif // DOCTORSTATISTICDIALOG_H
