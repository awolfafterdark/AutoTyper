#include "keyboard.h"

#ifdef _WIN32
Keyboard::Keyboard()
{
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
}

void Keyboard::sendStringInput(QString inputString)
{
    inputString = inputString.toUpper();
    if (inputString != "")
    {
        for (int i = 0; i < inputString.size(); i++)
        {
            input.ki.dwFlags = 0;
            input.ki.wVk = inputString[i].toLatin1();
            //SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;
            //SendInput(1, &input, sizeof(INPUT));
        }
        input.ki.dwFlags = 0;
        input.ki.wVk = VK_RETURN;
        //SendInput(1, &input, sizeof(INPUT));

        input.ki.dwFlags = KEYEVENTF_KEYUP;
        //SendInput(1, &input, sizeof(INPUT));
    }
}
#endif

#ifdef __linux__

XKeyEvent event;
Display* display;
    Keyboard::Keyboard()
    {
        display = XOpenDisplay(0);
        event.display = display;
        event.same_screen = true;
        event.time = CurrentTime;
        event.state = 0;
        event.x = 1;
        event.y = 1;
        event.x_root = 1;
        event.y_root = 1;
    }

    Keyboard::~Keyboard()
    {
        XCloseDisplay(display);
    }

    void Keyboard::generateKeyEvent(int key, int keyAction)
    {
        Window currentWin;
        int revert;
        XGetInputFocus(display, &currentWin, &revert);
        event.window = currentWin;
        event.root = XDefaultRootWindow(display);
        event.type = keyAction;
        event.keycode = XKeysymToKeycode(display, key);

    }

    void Keyboard::sendStringInput(QString inputString)
    {
        if (inputString != "")
        {
            for (int i = 0; i < inputString.size(); i++)
            {
                generateKeyEvent(inputString[i].toLatin1(), KeyPress);
                XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent*)&event);

                event.type = KeyRelease;
                XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent*)&event);
            }
            generateKeyEvent(XK_Return, KeyPress);
            XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent*)&event);

            event.type = KeyRelease;
            XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent*)&event);
            XFlush(display);
        }
    }

#endif
