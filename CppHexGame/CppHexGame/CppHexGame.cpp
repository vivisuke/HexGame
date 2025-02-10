#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	Board bd(3);
	bd.put(1, 1, BLACK);
	bd.print();
	//
    std::cout << "\nOK.\n";
}
