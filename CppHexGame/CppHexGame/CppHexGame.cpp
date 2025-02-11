#include <iostream>
#include <assert.h>
#include "Board.h"

using namespace std;

int main()
{
	Board bd(3);
	bd.put(1, 1, BLACK);
	bd.put(2, 2, BLACK);
	assert( !bd.put(1, 0, BLACK) );
	bd.print();
	bd.print_gid();
	assert( bd.put(2, 1, BLACK) );
	bd.print();
	bd.print_gid();
	//
    std::cout << "\nOK.\n";
}
