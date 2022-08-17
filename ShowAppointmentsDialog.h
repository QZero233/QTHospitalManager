#ifndef SHOWAPPOINTMENTSDIALOG_H
#define SHOWAPPOINTMENTSDIALOG_H

#include <QDialog>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QMenu>

#include "AppointmentService.h"

#include "AppointmentModel.h"

namespace Ui {
class ShowAppointmentsDialog;
}

class ShowAppointmentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAppointmentsDialog(const vector<Appointment>& appointments,QWidget *parent = nullptr);
    explicit ShowAppointmentsDialog(int departmentId,QWidget *parent = nullptr);
    ~ShowAppointmentsDialog();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ShowAppointmentsDialog *ui;

    void initUI();

    void displayAppointments();

    AppointmentModel* model;

    AppointmentService service;

    QMenu* tableMenu;
    QAction* deleteAction;
    QAction* addAction;

    int contextMenuSelectedIndex=-1;
    int departmentId=-1;
private slots:
    void dataTable_customContextMenuRequested(QPoint pos);
    void dataTable_delete_triggered();
    void dataTable_add_triggered();
};

#endif // SHOWAPPOINTMENTSDIALOG_H
