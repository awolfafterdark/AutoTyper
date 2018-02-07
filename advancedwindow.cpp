#include "advancedwindow.h"
#include "ui_advancedwindow.h"

AdvancedWindow::AdvancedWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedWindow)
{
    ui->setupUi(this);
}

AdvancedWindow::~AdvancedWindow()
{
    delete ui;
}

void AdvancedWindow::on_cancelButton_clicked()
{
    this->close();
}

void AdvancedWindow::on_ok_button_clicked()
{
    this->accept();
    this->close();
}

QString AdvancedWindow::getMessageBoxText() const { return ui->messageEdit->toPlainText(); }
void AdvancedWindow::setMessageBoxText(QString message) { ui->messageEdit->setText(message); }
void AdvancedWindow::setMessageTitle(QString title) { ui->titleLabel->setText("<font color='#5500fe'>Message Title: " + title + "</font>"); }
