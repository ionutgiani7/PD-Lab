// Lab1Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    HKEY hKey;
    HKEY hSystem, hCCS, hServices;

    
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM", 0, KEY_READ, &hSystem) != ERROR_SUCCESS) {
        cout << "Eroare SYSTEM\n";
        return 1;
    }

    if (RegOpenKeyExA(hSystem, "CurrentControlSet", 0, KEY_READ, &hCCS) != ERROR_SUCCESS) {
        cout << "Eroare CurrentControlSet\n";
        return 1;
    }

    if (RegOpenKeyExA(hCCS, "Services", 0, KEY_READ, &hServices) != ERROR_SUCCESS) {
        cout << "Eroare Services\n";
        return 1;
    }

    char subKeyName[256];
    DWORD index = 0;

    // Enumerãm serviciile
    while (true) {
        DWORD size = sizeof(subKeyName);

        if (RegEnumKeyExA(hServices, index, subKeyName, &size, NULL, NULL, NULL, NULL) == ERROR_NO_MORE_ITEMS)
            break;

        HKEY hSubKey;

        if (RegOpenKeyExA(hServices, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {

            DWORD typeValue;
            DWORD typeSize = sizeof(typeValue);
            DWORD type;

            // Citim Type
            if (RegQueryValueExA(hSubKey, "Type", NULL, &type, (LPBYTE)&typeValue, &typeSize) == ERROR_SUCCESS) {

                // Verificãm dacã e driver
                if (typeValue == 1 || typeValue == 2) {

                    char imagePath[1024];
                    DWORD imageSize = sizeof(imagePath);

                    if (RegQueryValueExA(hSubKey, "ImagePath", NULL, NULL, (LPBYTE)imagePath, &imageSize) == ERROR_SUCCESS) {
                        cout << subKeyName << " -> " << imagePath << endl;
                    }
                }
            }

            RegCloseKey(hSubKey);
        }

        index++;
    }

    // Închidem toate cheile
    RegCloseKey(hServices);
    RegCloseKey(hCCS);
    RegCloseKey(hSystem);

    return 0;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
