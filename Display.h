#pragma once

#include "IncludedLibraries.h"

class Display
{
public:
	Display();
	~Display();

	static uint16_t DrawWindow(int argc, char* argv[], char* title);
};

