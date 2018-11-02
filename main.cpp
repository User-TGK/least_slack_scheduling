#include "JobShop.h"
#include <fstream>
#include <iostream>
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " [Path to file]" << std::endl;
		return 1;
	}
	std::string fileName = argv[1];
	std::ifstream ifs;
	ifs.open(fileName);
	if (ifs.is_open())
	{
		JobShop j;
		j.schedule(&ifs, &std::cout);
	}
	else
	{
		std::cerr << "Could not open: " << argv[1] << std::endl;
	}
	return 0;
}