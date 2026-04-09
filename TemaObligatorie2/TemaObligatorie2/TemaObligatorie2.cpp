// TemaObligatorie2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <devpkey.h>
#include <initguid.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <tchar.h>
#include <iostream>

DEFINE_DEVPROPKEY(DEVPKEY_Device_BusNumber, 0x540b947e, 0x8b40, 0x45bc, 0xa8, 0xa2, 0x6a, 0x0b, 0x89, 0x4c, 0xbd, 0xa2, 13);
DEFINE_DEVPROPKEY(DEVPKEY_Device_Address, 0x540b947e, 0x8b40, 0x45bc, 0xa8, 0xa2, 0x6a, 0x0b, 0x89, 0x4c, 0xbd, 0xa2, 12);

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "cfgmgr32.lib")

int main() {
    // Enumerare device-uri
    HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        std::cerr << "Eroare la SetupDiGetClassDevs\n";
        return 1;
    }

    SP_DEVINFO_DATA devInfo;
    devInfo.cbSize = sizeof(devInfo);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfo); i++) {
        //  HardwareID (conține VID/PID)
        WCHAR hwId[1024];
        if (SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &devInfo,
            SPDRP_HARDWAREID,
            NULL,
            (PBYTE)hwId,
            sizeof(hwId),
            NULL))
        {
            wprintf(L"Device %d HardwareID: %s\n", i, hwId);
        }

        

        //  Adresa și bus number
        DEVPROPTYPE propType;
        ULONG size = 0;
        ULONG address = 0;
        ULONG busNum = 0;
        ULONG addressSize = sizeof(address);
        ULONG busNumSize = sizeof(busNum);

        CM_Get_DevNode_Property(devInfo.DevInst, &DEVPKEY_Device_Address, &propType, (PBYTE)&address, &addressSize, 0);
        CM_Get_DevNode_Property(devInfo.DevInst, &DEVPKEY_Device_BusNumber, &propType, (PBYTE)&busNum, &busNumSize, 0);

        wprintf(L"  Bus=%lu, Address=%lu\n", busNum, address);

        //  Friendly Name / DeviceDesc
        WCHAR desc[1024];
        if (SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &devInfo,
            SPDRP_DEVICEDESC,
            NULL,
            (PBYTE)desc,
            sizeof(desc),
            NULL))
        {
            wprintf(L"  Description: %s\n", desc);
        }

        wprintf(L"----------------------------\n");
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
    return 0;
}


