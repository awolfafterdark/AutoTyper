#ifndef KEYBOARD_H
#define KEYBOARD_H

//Global includes
#include <QString>
#include <QDebug>

#ifdef _WIN32               //Include below if running on x86/x64 version of Windows
#include <qt_windows.h>

class Keyboard
{
public:
    Keyboard::Keyboard();
    void sendStringInput(QString);
private:

    INPUT input;
};
#endif

#if __linux__             //Include below if running on linux.

#include <X11/Xlib.h>
#include <X11/keysym.h>

class Keyboard
{
public:
    Keyboard();
    ~Keyboard();

    void sendStringInput(QString);
private:
    void generateKeyEvent(int key, int keyAction);

};
#endif

#if __APPLE__             //Include below if running on OSX.

#endif

#endif // KEYBOARD_H
