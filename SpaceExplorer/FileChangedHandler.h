#pragma once

#include <vector>
#include <tuple>
#include <string.h>

#include "IFileChangedListener.h"

typedef std::tuple<IFileChangedListener*, std::string> FileChangedListenerPair;

class FileChangedHandler 
{
	std::vector<FileChangedListenerPair> listeners;

public:
	FileChangedHandler();
	~FileChangedHandler();

	void RegisterListener(IFileChangedListener *l, std::string path);
};