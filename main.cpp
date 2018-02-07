#include <QApplication>
#include "autotyperwindow.h"
#include "advancedwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoTyperWindow w;
    w.show();

    return a.exec();
}
