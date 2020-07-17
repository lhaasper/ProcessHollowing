
#include "Windows.h"
#include "TlHelp32.h"
#include <iostream>
#include <iostream>
#include<Windows.h>
#include <tchar.h>


using namespace std;

void InjectDLL(DWORD proccessId)
{
	const char* dllPath = "C:\\Program Files\\WinRAR\\RAR.dll"; //DLL-PATH HERE (can be anywhere)
	HANDLE hTargetProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, proccessId); //assigns perms
	if (hTargetProcess)
	{
		LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
		LPVOID RemoteString = VirtualAllocEx(hTargetProcess, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); //alocates virtual memory
		WriteProcessMemory(hTargetProcess, RemoteString, dllPath, strlen(dllPath), NULL); //writes memory to the process
		CreateRemoteThread(hTargetProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, (LPVOID)RemoteString, NULL, NULL); //creates a remote thread to the handle
		Sleep(1000); //wait
		exit(0); //exit
	}
}

DWORD PID(LPCSTR proc) //getting the windopws PID
{
	DWORD pid;
	HWND Program = FindWindowA(NULL, proc);
	while (Program == NULL)
	{
		Program = FindWindowA(NULL, proc);
		Sleep(2000);
		system("cls");
	}
	if (Program != NULL)
	{
		GetWindowThreadProcessId(Program, &pid); //gets the PID of the definded window
	}
	return pid;
}

int main()
{

	system("start Notepad.exe");
	//IN ORDERE TO USE IT FOR TASK MANAGER: system("start Taskmgr.exe");

	Sleep(900); //wait for notepad to get starded
	
	
	//InjectDLL(PID("Unbenannt - Editor")); /IGNORE - Only for german pc's 
  
        // You should add a language switch using an if statement.
	
	
  	//IN ORDERE TO USE IT FOR TASK MANAGER: InjectDLL(PID("Task Manager"));

	InjectDLL(PID("Untitled - Notepad")); //- Input any windows process here, you can use: Regedit, Taskmanager, RegASM and much more.
	
	
	
	
	
	return 0;

}
