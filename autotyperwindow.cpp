#include "autotyperwindow.h"
#include "ui_autotyperwindow.h"

AutoTyperWindow::AutoTyperWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AutoTyperWindow)
{
    ui->setupUi(this);
    setFixedSize(250, 250);

    connect(ui->actionExit, SIGNAL(triggered()),this, SLOT(close())); //Add the 'close' action to the 'exit' button in the menu.

    for ( int i = 0; i < MAX_MESSAGE_COUNT; i++)
        sMessageInfo.push_back(tempVector);

    sMessageInfo[0].push_back("Default1"); //Add Default1 to 0 as message title.
    sMessageInfo[0].push_back("Default");  //Add Default to 0 as message.
    loadMessageInUI(0);
}

AutoTyperWindow::~AutoTyperWindow()
{
    delete ui;
}

void AutoTyperWindow::on_pushMessageSlot_clicked()
{
    if ((ui->selectorCombo->count() == 0))       //Check if this is the first index being added to the combo box
    {
        ui->titleEdit->setDisabled(false);       //If so, re-enable the title and message boxes.
        ui->messageEdit->setDisabled(false);
        ui->advancedButton->setDisabled(false);
    }
    if (ui->selectorCombo->count() < MAX_MESSAGE_COUNT)
    {
        QString sTitle = "Default" + QString::number(ui->selectorCombo->count() + 1); //Generate a title for the new message.
        sMessageInfo[ui->selectorCombo->count()].push_back(sTitle);                   //Add .. to last index as message title.
        sMessageInfo[ui->selectorCombo->count()].push_back("Default");                //Add Default to last index as message.
        ui->selectorCombo->addItem(sTitle);                                           //Add a new message to the combo box with the new title.
        ui->selectorCombo->setCurrentIndex((ui->selectorCombo->count() - 1));         //Set your current message to the new message.
    }
}

void AutoTyperWindow::on_popMessageSlot_clicked()
{
    if (ui->selectorCombo->count() > 0)
    {
        sMessageInfo.removeAt(ui->selectorCombo->currentIndex());
        sMessageInfo.push_back(tempVector);
        ui->selectorCombo->removeItem(ui->selectorCombo->currentIndex());                   //Remove the current message.
    }
    if ((ui->selectorCombo->count() == 0) && (ui->selectorCombo->isEnabled() == true)) //Check if there are no more items within the combo box.
    {
        ui->titleEdit->setDisabled(true);
        ui->messageEdit->setDisabled(true);
        ui->advancedButton->setDisabled(true);
    }
}

void AutoTyperWindow::loadMessageInUI(int iIndex)
{
    if (iIndex >= 0)
    {
        ui->titleEdit->setText(sMessageInfo[iIndex][0]);    //Set UI's "title box" to the desired message.
        ui->messageEdit->setText(sMessageInfo[iIndex][1]);  //Set UI's "message box" to the desired message.
    }
}

void AutoTyperWindow::on_selectorCombo_currentIndexChanged(int index)
{
    loadMessageInUI(index);
}

void AutoTyperWindow::on_titleEdit_textChanged(const QString &arg1)
{
    sMessageInfo[ui->selectorCombo->currentIndex()][0] = arg1;  //Save the text entered into "title box".
    ui->selectorCombo->setItemText(ui->selectorCombo->currentIndex(), arg1);
}

void AutoTyperWindow::on_messageEdit_textChanged(const QString &arg1)
{
    sMessageInfo[ui->selectorCombo->currentIndex()][1] = arg1;  //Save the text entered into "message box".
}

void AutoTyperWindow::on_mainButton_clicked()
{
    if (sMessageInfo[0].isEmpty())                              //Checks if there are any message.
    {
        QMessageBox(QMessageBox::Information, "Information",
                    "You are unable to start because you do not have any messages to type.",
                    QMessageBox::Ok).exec();
        return;
    }
    ui->mainButton->setText("STOP!");
    ui->mainButton->blockSignals(true);
    int timingBetween = ui->intervalSBox->value();
    for (int i = 0; i < MAX_MESSAGE_COUNT; i++)
    {
        if (sMessageInfo[i].isEmpty() == false)
            messagesToType[i] = sMessageInfo[i][1];
        else
            continue;
    }

    int messageIncrement = 0;
    QTime *currentTimer = new QTime;
    currentTimer->start();
    while ((ui->mainButton->isDown() != true) &&  (QWidget::isHidden() == false))
    {
        QCoreApplication::processEvents();                              //Keep QT's event handler happy.
        if (currentTimer->elapsed() > (timingBetween*1000))             //Checks if we have reach the user predefined interval.
        {
            currentTimer->restart();
            keyboard.sendStringInput(messagesToType[messageIncrement]);
            if ((messageIncrement == MAX_MESSAGE_COUNT-1) || (messagesToType[messageIncrement + 1].isEmpty()))
                messageIncrement = 0;
            else
                messageIncrement++;
        }
        ui->intervalLCDCount->display(currentTimer->elapsed()/1000);
    }

    while (ui->mainButton->isDown())                                    //The point of this is to prevent the function from running again.
        QCoreApplication::processEvents();

    for (int i = 0; i < MAX_MESSAGE_COUNT; i++)
    {
        messagesToType[i] = "";                  //Reset the message output array.
    }

    ui->mainButton->setText("Start");
    ui->intervalLCDCount->display(0);
    ui->mainButton->blockSignals(false);
    delete currentTimer;
}

void AutoTyperWindow::on_advancedButton_clicked()
{
    AdvancedWindow advancedWindow(this);                              //Create advance window using 'autotyperwindow' as the parent.
    advancedWindow.setMessageTitle(ui->titleEdit->text());            //Set the messageTitle of the dialog to the current message title.
    advancedWindow.setMessageBoxText(ui->messageEdit->text());        //Set the messageEdit of the dialog to the current message.

    if(advancedWindow.exec() == QDialog::Accepted)
        ui->messageEdit->setText(advancedWindow.getMessageBoxText()); //If 'OK' is pressed, set the new message.

}
