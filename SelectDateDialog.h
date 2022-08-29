#ifndef SELECTDATEDIALOG_H
#define SELECTDATEDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDateDialog;
}

class SelectDateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDateDialog(QWidget *parent = nullptr);
    ~SelectDateDialog();

    QDate getDate();
    int getDays();
private:
    Ui::SelectDateDialog *ui;
};

#endif // SELECTDATEDIALOG_H
