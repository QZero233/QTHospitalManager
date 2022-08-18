#ifndef INPUTTELDIALOG_H
#define INPUTTELDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class InputTelDialog;
}

class InputTelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputTelDialog(QWidget *parent = nullptr);
    ~InputTelDialog();

    QString getTel();
private:
    Ui::InputTelDialog *ui;
};

#endif // INPUTTELDIALOG_H
