#pragma once
#define WIN32_LEAN_AND_MEAN //Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <iostream>
#include <string>
#include <istream>
#include <iostream>
#include <string>
#include <TlHelp32.h>
using namespace std;
VOID main()
{
	AllocConsole(); //alocate console to the remote thread
	FILE* f; //Create File Pointer
		//freopen_s(&f, "CONOUT$", "w", stdout); //Setup some console shit to allow for output and user input
	//freopen_s(&f, "CONIN$", "r", stdin);
	//freopen_s(&f, "CONOUT$", "w", stderr);
	system("color b"); //Not the best way of changing the console color, but what ever
	SetConsoleTitle(L"MajorCC"); //Set the console title
	system("echo Hey");


	Sleep(2000);

}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call) //Find reason for DLLMain Call
	{
	case DLL_PROCESS_ATTACH: //If the reason for the call is attach;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL); 
		break;
	}
	return TRUE; //Return true
}
