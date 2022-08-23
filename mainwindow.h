#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>

#include "DepartmentService.h"
#include "DepartmentModel.h"
#include "DepartmentDelegate.h"

#include "DutyModel.h"
#include "DutyDelegate.h"

#include "DoctorModel.h"
#include "DoctorDelegate.h"

#include "UserModel.h"
#include "UserDelegate.h"

#include "TableDutyModel.h"

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
    void on_dataTable_doubleClicked(const QModelIndex &index);

    void dataTable_customContextMenuRequested(QPoint pos);

    void dataTable_edit_triggered();

    void dataTable_delete_triggered();

    void dataTable_appointments_triggered();

    void on_actionAdd_triggered();

    void on_actionduties_triggered();

    void on_actiondepartments_triggered();

    void on_actiondoctors_triggered();

    void on_actionaddDoctor_triggered();

    void on_actionaddDuty_triggered();

    void on_actionUsers_triggered();

    void on_actionAddUser_triggered();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

    virtual void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow *ui;

    DepartmentModel* model;
    TableDutyModel* dutyModel=NULL;
    DoctorModel* doctorModel=NULL;
    UserModel* userModel=NULL;

    DepartmentDelegate* delegate=new DepartmentDelegate();
    DutyDelegate* dutyDelegate=new DutyDelegate();
    DoctorDelegate* doctorDelegate=new DoctorDelegate();
    UserDelegate* userDelegate=new UserDelegate();

    DepartmentService departmentService;

    QMenu* tableMenu;
    QAction* editAction;
    QAction* deleteAction;
    QAction* appointmentsAction;

    int contextMenuSelectedIndex=-1;
    int selectedColumn=-1;

    void showEditDepartmentDialog(int id);

    void showAppointmentsDialog(int id);

    int mode=0;

    void controlMenuVisibilityByMode();

    static const int MODE_DEPARTMENT=0;
    static const int MODE_DUTY=1;
    static const int MODE_DOCTOR=2;
    static const int MODE_USER=3;
};
#endif // MAINWINDOW_H
