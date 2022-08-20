#ifndef INPUTPASSWORDDIALOG_H
#define INPUTPASSWORDDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class InputPasswordDialog;
}

class InputPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputPasswordDialog(QWidget *parent = nullptr);
    ~InputPasswordDialog();

    QString getPwd();
private:
    Ui::InputPasswordDialog *ui;
};

#endif // INPUTPASSWORDDIALOG_H
