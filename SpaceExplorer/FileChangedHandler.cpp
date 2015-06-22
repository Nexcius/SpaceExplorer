#include "FileChangedHandler.h"



FileChangedHandler::FileChangedHandler() 
{

}


FileChangedHandler::~FileChangedHandler()
{

}


void FileChangedHandler::RegisterListener(IFileChangedListener *l, std::string path) 
{

	listeners.push_back(FileChangedListenerPair(l, path));
};