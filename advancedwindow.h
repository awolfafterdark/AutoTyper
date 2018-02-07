#ifndef ADVANCEDWINDOW_H
#define ADVANCEDWINDOW_H

#include <QDialog>

namespace Ui {
class AdvancedWindow;
}

class AdvancedWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedWindow(QWidget *parent = 0);
    ~AdvancedWindow();

    QString getMessageBoxText() const;

    void setMessageTitle(QString);
    void setMessageBoxText(QString);
private slots:
    void on_cancelButton_clicked();

    void on_ok_button_clicked();

private:
    Ui::AdvancedWindow *ui;
};

#endif // ADVANCEDWINDOW_H
