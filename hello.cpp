#include <iostream>
#include "hello.hpp"

void hello(int t)
{
	for (int i = 0; i < t; ++i) {
		std::cout << "Hello (" << i << ")" << std::endl;
	}
}
