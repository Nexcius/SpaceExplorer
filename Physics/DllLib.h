#pragma once

#define DLLExport __declspec(dllexport)

extern "C" {
	DLLExport int Init();
	DLLExport int Update(float time);
	DLLExport int Unload();
}