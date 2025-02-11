#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	Board bd(3);
	bd.put(1, 1, BLACK);
	bd.print();
	bd.print_gid();
	//
    std::cout << "\nOK.\n";
}
