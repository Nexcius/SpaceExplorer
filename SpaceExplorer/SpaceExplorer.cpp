#include "stdafx.h"


#include <iostream>
#include <chrono>
#include <thread>

#include "LibraryHandler.h"

/*
typedef int(*FuncNoParams)();
typedef int(*FuncWithParams)(int value);
*/

int main(int argc, char* argv[])
{


	LibraryHandler *h = new LibraryHandler();
	/*h->Load("Physics.dll");
	while (true) {
		h->Update(4.5f);
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}*/

	h->WatchForChanges();
	
	delete h;


	return EXIT_SUCCESS;
}

