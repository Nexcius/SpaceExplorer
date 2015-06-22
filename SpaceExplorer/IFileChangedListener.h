#pragma once

class IFileChangedListener {
public:
	virtual void FileChanged(char *filename);
};