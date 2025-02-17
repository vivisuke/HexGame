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
	if( false ) {
		const int NR = 10000;
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
	}
	if( false ) {
		bd.saveStatePut(1, 0, BLACK);
		bd.saveStatePut(1, 2, BLACK);
		bd.print();
		bd.print_gid();
		bd.saveStatePut(1, 1, BLACK);
		bd.print();
		bd.print_gid();
		bd.undo(1, 1);
		bd.print();
		bd.print_gid();
	}
	if( false ) {
		Board bd(3);
		bd.print();
		uchar next = WHITE;
		int n_empty = bd.n_empty() - 1;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, BLACK);
					int ev;
					if( next == BLACK )
						ev = bd.min_level(-INT_MAX, INT_MAX, n_empty);
					else
						ev = bd.max_level(-INT_MAX, INT_MAX, n_empty);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
	if( true ) {
		Board bd(3);
		bd.print();
		uchar next = BLACK;
		int n_empty = bd.m_width * bd.m_width - 1;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev;
					if( next == BLACK )
						ev = bd.min_level(-INT_MAX, INT_MAX, n_empty);
					else
						ev = bd.max_level(-INT_MAX, INT_MAX, n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
	if( true ) {
		Board bd(3);
		bd.saveStatePut(1, 1, BLACK);
		bd.print();
		uchar next = WHITE;
		int n_empty = bd.m_width * bd.m_width - 1;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev;
					if( next == BLACK )
						ev = bd.min_level(-INT_MAX, INT_MAX, n_empty);
					else
						ev = bd.max_level(-INT_MAX, INT_MAX, n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
	if( true ) {
		Board bd(3);
		bd.saveStatePut(1, 1, BLACK);
		bd.saveStatePut(2, 0, WHITE);
		bd.print();
		uchar next = BLACK;
		int n_empty = bd.m_width * bd.m_width - 1;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev;
					if( next == BLACK )
						ev = bd.min_level(-INT_MAX, INT_MAX, n_empty);
					else
						ev = bd.max_level(-INT_MAX, INT_MAX, n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
	if( false ) {
		Board bd(4);
		int n_empty = bd.m_width * bd.m_width - 1;
		for(int y = 0; y != bd.m_width; ++y) {
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, BLACK);
					int ev = bd.min_level(-INT_MAX, INT_MAX, n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl;
		bd.print();
		bd.print_gid();
	}
	if( false ) {
		Board bd(4);
		bd.saveStatePut(1, 2, BLACK);
		uchar next = WHITE;
		bd.print();
		int n_empty = bd.n_empty() - 1;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.min_level(-INT_MAX, INT_MAX, n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		//printf("n node = %d\n", bd.m_n_node);
		cout << "n node = " << bd.m_n_node << endl;
		//bd.print_gid();
	}
	if( false ) {
		Board bd(4);
		bd.saveStatePut(1, 2, BLACK);
		bd.saveStatePut(2, 0, WHITE);
		uchar next = BLACK;
		bd.print();
		int n_empty = bd.n_empty() - 1;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.max_level(-INT_MAX, INT_MAX, n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		//printf("n node = %d\n", bd.m_n_node);
		cout << "n node = " << bd.m_n_node << endl;
		//bd.print_gid();
	}
	if( false ) {
		Board bd(3);
		bd.saveStatePut(0, 0, BLACK);
		int n_empty = bd.m_width * bd.m_width - 2;
		for(int y = 0; y != bd.m_width; ++y) {
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, WHITE);
					int ev = bd.max_level(n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		bd.print();
		bd.print_gid();
	}
	if( false ) {
		Board bd(3);
		bd.saveStatePut(0, 0, BLACK);
		bd.saveStatePut(1, 1, WHITE);
		int n_empty = bd.m_width * bd.m_width - 3;
		for(int y = 0; y != bd.m_width; ++y) {
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, BLACK);
					int ev = bd.min_level(n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		bd.print();
		bd.print_gid();
	}
	if( false ) {
		Board bd(3);
		bd.saveStatePut(0, 0, BLACK);
		bd.saveStatePut(1, 1, WHITE);
		bd.saveStatePut(1, 0, BLACK);
		int n_empty = bd.m_width * bd.m_width - 4;
		for(int y = 0; y != bd.m_width; ++y) {
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, WHITE);
					int ev = bd.max_level(n_empty);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		bd.print();
		bd.print_gid();
	}
	if( false ) {
		Board bd(3);
		bd.saveStatePut(0, 0, BLACK);
		//bd.saveStatePut(1, 1, WHITE);
		int n_empty = bd.m_width * bd.m_width - 1;
		uchar next = WHITE;
		for(int y = 0; y != bd.m_width; ++y) {
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.min_max(BLACK+WHITE-next, n_empty - 1);
					printf("%3d ", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		printf("\n");
		bd.print();
		bd.print_gid();
	}

	//
    std::cout << "\nOK.\n";
}
