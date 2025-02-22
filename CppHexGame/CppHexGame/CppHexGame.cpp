#include <iostream>
#include <assert.h>
#include <chrono>
#include "Board.h"

using namespace std;

vector<int> evList4x4 = {-9, -7, -7, +6,  -7, -7, +8, -5,  -5, +8, -7, -7,  +6, -7, -7, -9};
vector<double> softmax_values;

int main()
{
#if 0
	calc_softmax(evList4x4, softmax_values);
	for(int y = 0; y != 4; ++y) {
		for(int x = 0; x != 4; ++x) {
			printf("%8.4f", softmax_values[y*4 + x]);
		}
		printf("\n");
	}
	printf("\n");
#endif

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
	if( true ) {
		Board bd(3);
		//bd.print();
		uchar next = BLACK;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
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
		bd.sel_move_MCTS_ev();
	}
	if( false ) {
		Board bd(3);
		bd.saveStatePut(0, 0, BLACK);
		bd.print();
		uchar next = WHITE;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					cout << (bd.m_cells[ix] == BLACK ? "  ●" : "  ◯");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
	if( false ) {
		Board bd(3);
		const int NR = 10000;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*3, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				int wcnt = 0;
				for(int i = 0; i != NR; ++i) {
					bd.init();
					auto won = bd.rollout(ix, BLACK);
					if( won == BLACK )
						++wcnt;
				}
				printf(" %2.1f%%", wcnt*100.0/NR);
			}
			printf("\n");
		}
		printf("\n");
	}
	if( false ) {
		Board bd(3);
		const int NR = 10000;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*3, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				int sum = 0;
				for(int i = 0; i != NR; ++i) {
					bd.init();
					sum += bd.rollout(ix, BLACK, bd.n_empty() - 1);
				}
				printf("%6.2f", (double)sum/NR);
			}
			printf("\n");
		}
		printf("\n");
	}
	if( false ) {
		Board bd(4);
		const int NR = 10000;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*3, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				int sum = 0;
				for(int i = 0; i != NR; ++i) {
					bd.init();
					sum += bd.rollout(ix, BLACK, bd.n_empty() - 1);
				}
				printf("%6.2f", (double)sum/NR);
			}
			printf("\n");
		}
		printf("\n");
	}
	if( false ) {
		Board bd(3);
		bd.saveStatePut(0, 0, BLACK);
		bd.saveStatePut(0, 2, WHITE);
		bd.print();
		uchar next = BLACK;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					cout << (bd.m_cells[ix] == BLACK ? "  ●" : "  ◯");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
#if 0
	if( true ) {
		Board bd(3);
		bd.saveStatePut(2, 1, BLACK);
		bd.print();
		uchar next = WHITE;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
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
		bd.saveStatePut(2, 1, BLACK);
		bd.saveStatePut(2, 0, WHITE);
		bd.print();
		uchar next = BLACK;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
	if( true ) {
		Board bd(3);
		bd.saveStatePut(2, 1, BLACK);
		bd.saveStatePut(2, 0, WHITE);
		bd.saveStatePut(0, 1, BLACK);
		bd.print();
		uchar next = WHITE;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					printf("  NA");
			}
			printf("\n");
		}
		("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
#endif
	if( false ) {
		Board bd(4);
		bd.print();
		auto start = chrono::high_resolution_clock::now(); // 計測開始
		uchar next = BLACK;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					cout << (bd.m_cells[ix] == BLACK ? "  ●" : "  ◯");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
		auto end = chrono::high_resolution_clock::now();   // 計測終了
		chrono::duration<double> elapsed_seconds = end - start; // 経過時間 (秒単位)
		cout << "処理時間: " << elapsed_seconds.count() << " 秒" << endl << endl;
	}
	if( false ) {
		Board bd(4);
		bd.saveStatePut(1, 1, BLACK);
		bd.print();
		uchar next = WHITE;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
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
		bd.saveStatePut(1, 1, BLACK);
		bd.saveStatePut(1, 2, WHITE);
		bd.print();
		uchar next = BLACK;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					cout << (bd.m_cells[ix] == BLACK ? "  ●" : "  ◯");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
	}
	if( false ) {
		Board bd(4);
		bd.saveStatePut(1, 1, BLACK);
		bd.saveStatePut(1, 2, WHITE);
		bd.saveStatePut(3, 1, BLACK);
		bd.print();
		uchar next = WHITE;
		for(int y = 0; y != bd.m_width; ++y) {
			cout << string(y*2, ' ');
			for(int x = 0; x != bd.m_width; ++x) {
				auto ix = bd.xyToIndex(x, y);
				if( bd.m_cells[ix] == EMPTY ) {
					bd.saveStatePut(ix, next);
					int ev = bd.alpha_beta(BLACK+WHITE-next);
					printf("%4d", ev);
					bd.undo(ix);
				} else
					cout << (bd.m_cells[ix] == BLACK ? "  ●" : "  ◯");
			}
			printf("\n");
		}
		printf("\n");
		cout << "n node = " << bd.m_n_node << endl << endl;
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
