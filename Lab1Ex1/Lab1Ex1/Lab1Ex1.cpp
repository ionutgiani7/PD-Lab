// Lab1Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>


using namespace std;

int main()
{
    HKEY hkey;
    string val;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
        "SYSTEM\\CurrentControlSet\\Services",
        0,
        KEY_READ,
        &hkey) != ERROR_SUCCESS)
        cout << "Eroare la deschidere" << endl;


    DWORD type;
    char data[512];
    unsigned long datasize = sizeof(data);

    if (RegQueryValueExA(hkey,
        "ImagePath",
        NULL,
        &type,
        (LPBYTE)data,
        &datasize) == ERROR_SUCCESS)
        cout << data << "asd" << endl;
    else
        cout << "Valoare inexistenta" << endl;
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
