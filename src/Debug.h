#pragma once
#include "stdafx.h"
class Debug
{
public:
	static void Log(std::string text) {
		std::cout << "INFO: " << text << std::endl;
	}
};

