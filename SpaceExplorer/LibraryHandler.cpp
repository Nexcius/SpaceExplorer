#include "stdafx.h"

#include "LibraryHandler.h"

#include <string>
#include <iostream>

#include <tchar.h>
#include <strsafe.h>


LibraryHandler::LibraryHandler()
{
	libraries = new std::vector<LibFunctions>();
}


LibraryHandler::~LibraryHandler()
{
	for (unsigned int i = 0; i < libraries->size(); i++) {
		//libraries->at(i).unloadFunc();
		FreeLibrary(libraries->at(i).lib);
	}
	delete libraries;
}


int LibraryHandler::Load(const char *path) {
	wchar_t pathWC[20];
	MultiByteToWideChar(0, 0, path, strlen(path) +1, pathWC, strlen(path) +1);

	LibFunctions libFuncs;

	libFuncs.lib = LoadLibrary(pathWC);
	if (libFuncs.lib == NULL) {
		printf("Unable to load library: %s\n", path);
	}
	else {
		printf("Loading library: %s\n", path);

		// Init()
		libFuncs.initFunc = (InitFunc)GetProcAddress(libFuncs.lib, "Init");
		if (libFuncs.initFunc == NULL) {
			printf("Unable to locate Init() function\n", path);
		}
		else {
			printf("Located Init() function\n");
		}

		// Update(float time)
		libFuncs.updateFunc = (UpdateFunc)GetProcAddress(libFuncs.lib, "Update");
		if (libFuncs.updateFunc == NULL) {
			printf("Unable to locate Update() function\n", path);
		}
		else {
			printf("Located Update() function\n");
		}

		// Unload()
		libFuncs.unloadFunc = (UnloadFunc)GetProcAddress(libFuncs.lib, "Unload");
		if (libFuncs.unloadFunc == NULL) {
			printf("Unable to locate Unload() function\n", path);
		}
		else {
			printf("Located Unload() function\n");
		}

		// Init library
		int initResult = libFuncs.initFunc();
		if (initResult) {
			printf("Init failed. Error code: %d\n", initResult);
			FreeLibrary(libFuncs.lib);
			return 1;
		}

		
		libFuncs.libName = new char[strlen(path) + 1];
		strcpy_s(libFuncs.libName, strlen(path) +1, path);
		libraries->push_back(libFuncs);
		printf("Library: %s loaded successfully\n", path);
		return 0;
	}

	return 1;
}


void LibraryHandler::Update(float time) {
	for (unsigned int i = 0; i < libraries->size(); i++) {
		int updateResult = libraries->at(i).updateFunc(time);
		if (updateResult) {
			printf("Update for library %s failed. Error code: %d\n", libraries->at(i).libName, updateResult);
		}
	}
}


BOOL GetLastWriteTime(HANDLE hFile, LPTSTR lpszString, DWORD dwSize)
{
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTC, stLocal;
	DWORD dwRet;

	// Retrieve the file times for the file.
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
		return FALSE;

	// Convert the last-write time to local time.
	FileTimeToSystemTime(&ftWrite, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	// Build a string showing the date and time.
	dwRet = StringCchPrintf(lpszString, dwSize,
		TEXT("%02d/%02d/%d  %02d:%02d"),
		stLocal.wMonth, stLocal.wDay, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute);

	if (S_OK == dwRet)
		return TRUE;
	else return FALSE;
}

std::wstring GetCurrentDirectory() {
	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);

	std::wstring filepath(buffer);
	std::wstring directory;

	const size_t last_slash_idx = filepath.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		directory = filepath.substr(0, last_slash_idx);
	}

	return directory;
}


void CheckAllFiles() {

	// CHECK WHAT FILE CHANGED
}


void LibraryHandler::WatchForChanges() {
	std::wstring dir = GetCurrentDirectory();

	HANDLE ChangeHandle = FindFirstChangeNotification(dir.c_str(), false, FILE_NOTIFY_CHANGE_LAST_WRITE);
	DWORD Wait = WaitForSingleObject(ChangeHandle, INFINITE);
	if (Wait == WAIT_OBJECT_0)
	{
		printf("CHANGE!\n");
		
		HANDLE hFile;
		TCHAR szBuf[MAX_PATH];


		

		hFile = CreateFile(L"D:\\Dev\\VisualStudio\\SpaceExplorer\\Debug\\Physics.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("CreateFile failed with %d\n", GetLastError());
		}
		if (GetLastWriteTime(hFile, szBuf, MAX_PATH))
			_tprintf(TEXT("Last write time is: %s\n"), szBuf);

		CloseHandle(hFile);
		
		FindNextChangeNotification(ChangeHandle);
	}
	else
	{
		printf("ASDASD\n");
	}
}

void LibraryHandler::StopWatchForChanges() {
	//FindCloseChangeNotification(ChangeHandle);
}