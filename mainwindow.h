#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QPoint>

#include <QMenu>
#include <QAction>

#include "DepartmentService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_dataTable_doubleClicked(const QModelIndex &index);

    void dataTable_customContextMenuRequested(QPoint pos);

    void dataTable_edit_triggered();

    void dataTable_delete_triggered();

    void dataTable_appointments_triggered();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;

    QStandardItemModel* model;

    DepartmentService departmentService;

    void displayDepartmentData();

    QMenu* tableMenu;

    int contextMenuSelectedId=-1;

    void showEditDepartmentDialog(int id);

    void showAppointmentsDialog(int id);
};
#endif // MAINWINDOW_H
