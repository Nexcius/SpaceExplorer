#pragma once
#include <vector>
#include <Windows.h>

typedef int(*InitFunc)();
typedef int(*UpdateFunc)(float time);
typedef int(*UnloadFunc)();


class LibraryHandler
{
private:
	typedef struct LibFunctions {
		char *libName;
		HINSTANCE lib;
		InitFunc initFunc;
		UpdateFunc updateFunc;
		UnloadFunc unloadFunc;
	};

	std::vector<LibFunctions> *libraries;

public:
	LibraryHandler();
	~LibraryHandler();

	int Load(const char *path);

	void Update(float);

	void WatchForChanges();
	void StopWatchForChanges();
};

