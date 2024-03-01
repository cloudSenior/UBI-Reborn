#pragma once

#include <iostream>


class
{
public:


	void warning(char const* message)
	{
        printf("Warning %s", message);
	}

	void error(char const* message)
	{
        printf("Error %s", message);
        throw std::runtime_error(message);
	}

private:
} Debugger;

