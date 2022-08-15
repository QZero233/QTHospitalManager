#ifndef SHOWAPPOINTMENTSDIALOG_H
#define SHOWAPPOINTMENTSDIALOG_H

#include <QDialog>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QMenu>

#include "AppointmentService.h"

namespace Ui {
class ShowAppointmentsDialog;
}

class ShowAppointmentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAppointmentsDialog(int departmentId,QWidget *parent = nullptr);
    ~ShowAppointmentsDialog();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ShowAppointmentsDialog *ui;

    int departmentId;

    void displayAppointments();

    QStandardItemModel* model;

    AppointmentService service;

    QMenu* tableMenu;
    QAction* deleteAction;
    QAction* addAction;

    int contextMenuSelectedId=-1;

private slots:
    void dataTable_customContextMenuRequested(QPoint pos);
    void dataTable_delete_triggered();
    void dataTable_add_triggered();
};

#endif // SHOWAPPOINTMENTSDIALOG_H
