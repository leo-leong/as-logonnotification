// Copyright (C) Microsoft. All rights reserved. 
#include <windows.h>
#include <WinWlx.h>

// Here is the entrance function for the DLL.
BOOL WINAPI LibMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    {

        // Disable DLL_THREAD_ATTACH & DLL_THREAD_DETACH
        // notification calls. This is a performance optimization
        // for multithreaded applications that do not need 
        // thread-level notifications of attachment or
        // detachment.

        DisableThreadLibraryCalls(hInstance);
    }
    break;
    }

    return TRUE;
}

// Here is the event handler for the Winlogon Logon event.
void WLEventLogon(PWLX_NOTIFICATION_INFO pInfo)
{

    // Print the name of the handler to debug output.
    // You can replace this with more useful functionality.
    OutputDebugString(TEXT("NOTIFY:  Entering WLEventLogon.\r\n"));
}

// Here is the event handler for the Winlogon Logoff event.
void WLEventLogoff(PWLX_NOTIFICATION_INFO pInfo)
{

    // Print the name of the handler to debug output.
    // You can replace this with more useful functionality.
    OutputDebugString(TEXT("NOTIFY:  Entering WLEventLogff.\r\n"));
}