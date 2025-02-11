#include <iostream>
#include <assert.h>
#include "Board.h"

using namespace std;

int main()
{
	Board bd(3);
	if( false ) {
		bd.put(1, 1, BLACK);
		bd.put(2, 2, BLACK);
		assert( !bd.put(1, 0, BLACK) );
		bd.print();
		bd.print_gid();
		assert( bd.put(2, 1, BLACK) );
		bd.print();
		bd.print_gid();
	}
	if( false ) {
		uchar col = BLACK;
		for(;;) {
			auto ix = bd.sel_move_random();
			if( bd.put(ix, col) ) break;
			col = (BLACK + WHITE) - col;
		}
		bd.print();
		bd.print_gid();
	}
	const int NR = 1000;
	for(int y = 0; y != bd.m_width; ++y) {
		for(int x = 0; x != bd.m_width; ++x) {
			auto ix = bd.xyToIndex(x, y);
			int wcnt = 0;
			for(int i = 0; i != NR; ++i) {
				bd.init();
				auto won = bd.rollout(ix, BLACK);
				if( won == BLACK )
					++wcnt;
			}
			printf("%.1f%% ", wcnt*100.0/NR);
		}
		printf("\n");
	}
	printf("\n");

	//
    std::cout << "\nOK.\n";
}
