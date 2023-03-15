#include <windows.h>
#include <npapi.h>
#include <string>
#include <iostream>


typedef DWORD(*LogonFunc)(LPCWSTR pszUserName, LPCWSTR pszDomainName, LPCWSTR pszPassword);

struct NPLOGONNOTIFY_DISPATCH_TABLE
{
    LogonFunc pfnlogonFunc;
};


DWORD WINAPI MyLogonNotify(LPCWSTR pszUserName, LPCWSTR pszDomainName, LPCWSTR pszPassword)
{
    // Logon notification code here
    std::string logPath = "c:\\temp\\MyLogonNotify.log";
    auto cstr = logPath.c_str();
    HANDLE fileHandle = CreateFileA(cstr, GENERIC_WRITE, NULL, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    //TODO: replace text with date and username
    std::string text = "Hello World!";
	DWORD bytesWritten{ 0 };
	if (!WriteFile(fileHandle, text.c_str(), text.length(), &bytesWritten, NULL))
	{
		std::cerr << "Failed to write to file..." << std::endl;
		return 1;
	}

    CloseHandle(fileHandle);
    return 0;
}

// Entry point for the network provider DLL
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hInstance);
        break;
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}

// NPLogonNotify function table
NPLOGONNOTIFY_DISPATCH_TABLE g_NpLogonNotifyDispatchTable = {
    MyLogonNotify
};

// Returns the NPLogonNotify function table
extern "C" void WINAPI NpGetLogonNotifyDispatchTable(NPLOGONNOTIFY_DISPATCH_TABLE * pDispatchTable)
{
    pDispatchTable->pfnlogonFunc = &MyLogonNotify;
}
