#ifndef TEST_H
#define TEST_H

#include <iostream>

class Test
{
public:
	int sumAndPrint(int x2, int y2) 
	{ 
		std::cout << x2 + y2 << std::endl; 
		return x2 + y2; 
	}

	int sumAndPrint2()
	{
		std::cout << x + y << std::endl;
		return x + y;
	}

private:
	const int x = 50;
	const int y = 50;
};

#endif