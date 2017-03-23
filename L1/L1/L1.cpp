// L1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Application.h"


int main(int argc, char *argv[])
{
	try
	{
		CApplication app(argv[1], argv[2]);
		app.OutputResults();
		return 0;
	}
	catch (...)
	{
		std::cerr << "Error!" << std::endl;
		return 1;
	}
    
}

