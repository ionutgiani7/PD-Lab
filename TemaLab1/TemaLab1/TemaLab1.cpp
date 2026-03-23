// TemaLab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>


using namespace std;

int main()
{
    HKEY hkey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
        "SYSTEM\\CurrentControlSet\\Services",
        0,
        KEY_READ,
        &hkey) != ERROR_SUCCESS)
        cout << "Eroare la deschiderea subcheii" << endl;

    char subkeyname[256];
    DWORD index = 0;

    while (true) {
        DWORD size = sizeof(subkeyname);
        if (RegEnumKeyExA(hkey, index, subkeyname, &size, NULL, NULL, NULL, NULL) == ERROR_NO_MORE_ITEMS)
            break;
        cout << "Subcheia: " << subkeyname << endl;
        index++;
    }

    RegCloseKey(hkey);
    return 0;

}


