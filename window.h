#ifndef WINDOW_H
#define WINDOW_H

#include <QDebug>
#include <qt_windows.h>
#include "psapi.h"

class Window
{
public:
    QString getActiveProcessName();
private:
    QString processName;
    char *buffer[255];
};

#endif // WINDOW_H
