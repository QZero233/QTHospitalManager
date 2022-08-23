#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>


#include "DepartmentModel.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(User user,QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:

    void on_actionSelect_triggered();

    void on_dataTable_doubleClicked(const QModelIndex &index);

    void on_actionQueryAppointment_triggered();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

    virtual void closeEvent(QCloseEvent* event) override;
private:
    Ui::RegistrationWindow *ui;

    DepartmentModel* model;

    User currentUser;
};

#endif // REGISTRATIONWINDOW_H
