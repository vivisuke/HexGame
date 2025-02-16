#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include "Board.h"

using namespace std;

std::mt19937 rgen(std::random_device{}()); // シードを設定

//--------------------------------------------------------------------------------
double MCTSNode::calculate_ucb(double c_puct) const {
	//if( m_visits == 0 )
	//	return INT_MAX;
	auto t1 = (double)m_wins / m_visits;		//	勝率
	auto t2 = c_puct * sqrt(log(m_parent->m_visits) / (double)m_visits);	// 探索
	return t1 + t2;
}
MCTSNode* MCTSNode::select_child_ucb(double c_puct) {
	MCTSNode *best = nullptr;
	double max_ucb = -INT_MAX;
	for(auto i = 0; i != m_children.size(); ++i) {
		auto *node = &m_children[i];
		auto ucb = node->calculate_ucb(c_puct);
		if( node->m_visits == 0 )
			return node;
		if( ucb > max_ucb ) {
			max_ucb = ucb;
			best = node;
		}
	}
	return best;
}
//--------------------------------------------------------------------------------
MCTS::MCTS(const Board* board, uchar col)
	: m_board(board), m_col(col)
{
	//m_root = new MCTSNode();
}
void MCTS::do_expand(MCTSNode* node) {
	auto n = m_board->n_empty();
	node->m_children.resize(n);
	int i = 0;		//	子ノードインデックス
	uchar col = (BLACK + WHITE) - node->m_col;
	const auto ix9 = m_board->xyToIndex(m_board->m_width - 1, m_board->m_width - 1);
	for(auto ix = m_board->xyToIndex(0, 0); ix <= ix9; ++ix) {
		if(m_board->m_cells[ix] == EMPTY ) {
			auto &ch = node->m_children[i++];
			ch.m_ix = ix;
			ch.m_col = col;
			ch.m_wins = ch.m_visits = 0;
			ch.m_parent = node;
			ch.m_children.clear();
		}
	}
}
void MCTS::do_search(int itr) {
	for(int i = 0; i != itr; ++i) {
		Board bd(m_board->m_width);
		bd.copy_from(*m_board);
		auto *node = &m_root;
		while( !node->m_children.empty() ) {
		}
	}
}
//--------------------------------------------------------------------------------
Board::Board(int wd)
	: m_width(wd)
{
	m_ary_width = m_width + 2;
	m_ary_height = m_width + 2;
	m_ary_size = m_ary_width * m_ary_height;
	m_cells.resize(m_ary_size);
	for(auto &v : m_cells) v = BWALL;
	m_gid.resize(m_ary_size);
	m_gid_stack.reserve(1000*1000);
	m_n_node = 0;
	init();
}
void Board::init() {
	m_seq_gid = 0;
	//for(auto &v : m_cells) v = EMPTY;
	for(int y = 0; y != m_width; ++y) {
		auto ix = xyToIndex(0, y);
		m_cells[ix-1] = WWALL;
		m_cells[ix+m_width] = WWALL;
		for(int x = 0; x != m_width; ++x) {
			auto ix = xyToIndex(x, y);
			m_cells[ix] = EMPTY;
		}
	}
	for(auto &v : m_gid) v = 0;
}
void Board::copy_from(const Board &src) {
	*this = src;
}
int Board::n_empty() const {
	int cnt = 0;
	for(auto ix = xyToIndex(0, 0); ix <= xyToIndex(m_width-1, m_width-1); ++ix)
		if( m_cells[ix] == 0 )
			++cnt;
	return cnt;
}
const char *wstr[] = {"ａ", "ｂ", "ｃ", "ｄ", "ｅ", "ｆ", "ｇ", "ｈ", "ｉ", "ｊ", "ｋ"};
void Board::print() const {
	cout << "  ";
	for(int x = 0; x != m_width; ++x) {
		cout << wstr[x];
		//wcout << wstring(1, ('ａ' + x));
		//cout << (char)('a'+x) << " ";
	}
	cout << endl;

	for(int y = 0; y != m_width; ++y) {
		//cout << y+1 << " ";
		cout << string(y, ' ');
		printf("%2d", y+1);
		for(int x = 0; x != m_width; ++x) {
			auto ix = xyToIndex(x, y);
			//cout << (int)m_cells[ix] << " ";
			switch( m_cells[ix] ) {
#if 1
			case EMPTY: cout << "・"; break;
			case BLACK: cout << "●"; break;
			case WHITE: cout << "◯"; break;
#else
			case EMPTY: cout << ". "; break;
			case BLACK: cout << "X "; break;
			case WHITE: cout << "O "; break;
#endif
			}
		}
		cout << endl;
	}
	cout << endl;
}
void Board::print_gid() const {
	for(int y = 0; y != m_width; ++y) {
		cout << string(y, ' ');
		for(int x = 0; x != m_width; ++x) {
			auto ix = xyToIndex(x, y);
			cout << (int)m_gid[ix] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void Board::print_put_stack() const {
	for(auto ix : m_put_stack) {
		int x = ixToX(ix);
		int y = ixToY(ix);
		printf("%c%d ", (0x61+x), y+1);
	}
	printf("\n");
}
bool Board::find_horz(uchar gid, int y) {
	for(int x = 0; x != m_width; ++x) {
		if( m_gid[xyToIndex(x, y)] == gid )
			return true;
	}
	return false;
}
bool Board::find_vert(uchar gid, int x) {
	for(int y = 0; y != m_width; ++y) {
		if( m_gid[xyToIndex(x, y)] == gid )
			return true;
	}
	return false;
}
bool Board::put(int x, int y, uchar col) {
	auto ix = xyToIndex(x, y);
	return put(ix, col);
}
bool Board::put(int ix, uchar col) {
	m_put_stack.push_back(ix);
	m_cells[ix] = col;
	update_gid(ix, col);
	auto gid = m_gid[ix];
	if( col == BLACK ) {
		return find_horz(gid, 0) && find_horz(gid, m_width-1);		//	上下辺と連結？
	} else {
		return find_vert(gid, 0) && find_vert(gid, m_width-1);		//	左右辺と連結？
	}
}
void Board::saveState() {
	m_seq_stack.push_back(m_seq_gid);
	int ix = xyToIndex(0, 0);
	int ix9 = xyToIndex(m_width-1, m_width-1);
	for(; ix <= ix9; ++ix) {
		if( m_cells[ix] < BWALL )
			m_gid_stack.push_back(m_gid[ix]);
	}
}
bool Board::saveStatePut(int ix, uchar col) {
	saveState();
	return put(ix, col);
}
void Board::undo(int ix) {
	m_seq_gid = m_seq_stack.back();
	m_seq_stack.pop_back();
	m_put_stack.pop_back();
	m_cells[ix] = EMPTY;
	int ix0 = xyToIndex(0, 0);
	int i = xyToIndex(m_width-1, m_width-1);
	for (; i >= ix0; --i ) {
		if( m_cells[i] < BWALL ) {
			m_gid[i] = m_gid_stack[m_gid_stack.size() - 1];
			m_gid_stack.pop_back();
		}
	}
}
void Board::update_gid_sub(int ix, int ix2) {
	if( m_cells[ix2] != m_cells[ix] ) return;
	if (m_gid[ix] == 0)		// 最初の連結の場合
		m_gid[ix] = m_gid[ix2];
	else if( m_gid[ix] != m_gid[ix2] ) {		// グループid のマージが必要
		auto o = m_gid[ix2];
		auto n = m_gid[ix];
		for(auto i = xyToIndex(0, 0); i <= xyToIndex(m_width-1, m_width-1); ++i) {
			if (m_gid[i] == o)
				m_gid[i] = n;
		}
	}
}
void Board::update_gid(int ix, uchar col) {
	update_gid_sub(ix, ix-m_ary_width);
	update_gid_sub(ix, ix-m_ary_width+1);
	update_gid_sub(ix, ix-1);
	update_gid_sub(ix, ix+1);
	update_gid_sub(ix, ix+m_ary_width-1);
	update_gid_sub(ix, ix+m_ary_width);
	if( m_gid[ix] == 0 ) {
		m_gid[ix] = ++m_seq_gid;
	}
}
int Board::sel_move_random() const {
	vector<int> lst;
	for(int y = 0; y != m_width; ++y) {
		for(int x = 0; x != m_width; ++x) {
			auto ix = xyToIndex(x, y);
			if( m_cells[ix] == EMPTY )
				lst.push_back(ix);
		}
	}
	if( lst.empty() ) return 0;
	return lst[rgen() % lst.size()];
}
uchar Board::rollout(int ix, uchar col) {
	if( put(ix, col) ) return col;
	for(;;) {
		col = (BLACK + WHITE) - col;
		ix = sel_move_random();
		if( put(ix, col) ) return col;
	}
}
int Board::min_level(int alpha, int beta, int n_empty) {
	--n_empty;
	int ix = xyToIndex(0, 0);
	int ix9 = xyToIndex(m_width-1, m_width-1);
	for(; ix <= ix9; ++ix) {
		if( m_cells[ix] == EMPTY ) {
			if( saveStatePut(ix, WHITE) ) {	//	put() → 終局の場合
				++m_n_node;
				undo(ix);
				return -(1 + n_empty);
			}
			beta = min(beta, max_level(alpha, beta, n_empty));
			undo(ix);
			if( alpha >= beta )
				break;
		}
	}
	return beta;
}
int Board::max_level(int alpha, int beta, int n_empty) {
	--n_empty;
	int ix = xyToIndex(0, 0);
	int ix9 = xyToIndex(m_width-1, m_width-1);
	for(; ix <= ix9; ++ix) {
		if( m_cells[ix] == EMPTY ) {
			if( saveStatePut(ix, BLACK) ) {	//	put() → 終局の場合
				++m_n_node;
				undo(ix);
				return (1 + n_empty);
			}
			alpha = max(alpha, min_level(alpha, beta, n_empty));
			undo(ix);
			if( alpha >= beta )
				break;
		}
	}
	return alpha;
}
int Board::min_level(int n_empty) {
	--n_empty;
	int ix = xyToIndex(0, 0);
	int ix9 = xyToIndex(m_width-1, m_width-1);
	int best_ev = INT_MAX;
	for(; ix <= ix9; ++ix) {
		if( m_cells[ix] == EMPTY ) {
			if( saveStatePut(ix, WHITE) ) {	//	put() → 終局の場合
				++m_n_node;
				//print_put_stack();
				undo(ix);
				return -(1 + n_empty);
			}
			auto ev = max_level(n_empty);
			if( ev < best_ev )
				best_ev = ev;
			undo(ix);
		}
	}
	//if( n_empty >= 7 ) {
	//	print();
	//	cout << "best_ev = " << best_ev << endl;
	//}
	return best_ev;
}
int Board::max_level(int n_empty) {
	--n_empty;
	int ix = xyToIndex(0, 0);
	int ix9 = xyToIndex(m_width-1, m_width-1);
	int best_ev = -INT_MAX;
	for(; ix <= ix9; ++ix) {
		if( m_cells[ix] == EMPTY ) {
			if( saveStatePut(ix, BLACK) ) {	//	put() → 終局の場合
				++m_n_node;
				//print_put_stack();
				undo(ix);
				return 1 + n_empty;
			}
			auto ev = min_level(n_empty);
			if( ev > best_ev )
				best_ev = ev;
			undo(ix);
		}
	}
	//if( n_empty >= 7 ) {
	//	print();
	//	cout << "best_ev = " << best_ev << endl;
	//}
	return best_ev;
}
int Board::min_max(uchar col, int n_empty) {
	--n_empty;
	int ix = xyToIndex(0, 0);
	int ix9 = xyToIndex(m_width-1, m_width-1);
	int best_ev = 0;
	if( col == BLACK ) {
		best_ev = -INT_MAX;
		for(; ix <= ix9; ++ix) {
			if( m_cells[ix] == EMPTY ) {
				if( saveStatePut(ix, col) ) {	//	put() → 終局の場合
					undo(ix);
					return 1 + n_empty;
				}
				auto ev = min_max(WHITE, n_empty);
				undo(ix);
				if( ev > best_ev )
					best_ev = ev;
			}
		}
	} else {	//	白番
		best_ev = INT_MAX;
		for(; ix <= ix9; ++ix) {
			if( m_cells[ix] == EMPTY ) {
				if( saveStatePut(ix, col) ) {	//	put() → 終局の場合
					undo(ix);
					return -(1 + n_empty);
				}
				auto ev = min_max(BLACK, n_empty);
				undo(ix);
				if( ev < best_ev )
					best_ev = ev;
			}
		}
	}
	return best_ev;
}
