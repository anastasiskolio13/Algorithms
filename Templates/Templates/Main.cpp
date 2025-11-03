#include "DFA.h"
#include <iostream>

int main() {
	DFA test({ 1, 2, 3 }, { 0, 1 }, 1, { 3 }, { { 2, 1 }, { 3, 1 }, { 3, 3 } });
	int finalState = test.DeltaStar({ 1, 0, 1, 1 }, 0, 1);
	if (test.IsAcceptingState(finalState))
		std::cout << "YES" << std::endl;
	else 
		std::cout << "NO"<< std::endl;
}