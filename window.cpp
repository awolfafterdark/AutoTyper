#include "window.h"

QString Window::getActiveProcessName()
{
    DWORD* processID = new DWORD;
    GetWindowThreadProcessId(GetForegroundWindow(), processID);
    DWORD pID = *processID;
    HANDLE hwnd = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pID);

    LPWSTR szProcessName;

    if (hwnd != NULL)
    {
        HMODULE hModule;
        DWORD dNeeded;
        if (EnumProcessModules(hwnd, &hModule, sizeof(hModule), &dNeeded))
        {
            GetModuleBaseName(hwnd, hModule, szProcessName, sizeof(szProcessName)/sizeof(LPWSTR));
        }
    }
    CloseHandle(hwnd);

    #ifdef UNICODE
        processName = QString::fromUtf16((ushort*)szProcessName);
    #else
        processName = QString::fromLocal8Bit(szProcessName);
    #endif

    return processName;
}
