#ifndef AUTOTYPERWINDOW_H
#define AUTOTYPERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTime>
#include <QList>
#include "keyboard.h"
#include "advancedwindow.h"
#include "ui_advancedwindow.h"

#define MAX_MESSAGE_COUNT 10 // Modify this to increase maximum amount of message allow within the dropdown list.

namespace Ui {
class AutoTyperWindow;
}

class AutoTyperWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AutoTyperWindow(QWidget *parent = 0);
    ~AutoTyperWindow();

private slots:
    void on_pushMessageSlot_clicked();
    void on_popMessageSlot_clicked();

    void on_selectorCombo_currentIndexChanged(int index);

    void on_titleEdit_textChanged(const QString &arg1);

    void on_messageEdit_textChanged(const QString &arg1);

    void on_mainButton_clicked();

    void on_advancedButton_clicked();

private:
    Ui::AutoTyperWindow *ui;
    Keyboard keyboard;
    //Message [..][0] = Message Title.
    //Message [..][1] = Message.
    QVector< QVector <QString> > sMessageInfo;
    QVector <QString> tempVector;
    QString messagesToType[MAX_MESSAGE_COUNT];

    //Private Functions

    //@return void;
    //@iIndex Message index in 'MessageInfo' to load into UI.
    void loadMessageInUI (int iIndex);

};

#endif // AUTOTYPERWINDOW_H
