#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include "Board.h"

using namespace std;

std::mt19937 rgen(std::random_device{}()); // �V�[�h��ݒ�

//--------------------------------------------------------------------------------
double MCTSNode::calculate_ucb(double c_puct) const {
	//if( m_visits == 0 )
	//	return INT_MAX;
	auto t1 = (double)m_wins / m_visits;		//	����
	auto t2 = c_puct * sqrt(log(m_parent->m_visits) / (double)m_visits);	// �T��
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
	int i = 0;		//	�q�m�[�h�C���f�b�N�X
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
	m_ary_width = m_width + 1;
	m_ary_height = m_width + 2;
	m_ary_size = m_ary_width * m_ary_height;
	m_cells.resize(m_ary_size);
	for(auto &v : m_cells) v = BWALL;
	m_gid.resize(m_ary_size);
	m_gid_stack.reserve(1000*1000);
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
const char *wstr[] = {"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��"};
void Board::print() const {
	cout << "  ";
	for(int x = 0; x != m_width; ++x) {
		cout << wstr[x];
		//wcout << wstring(1, ('��' + x));
		//cout << (char)('a'+x) << " ";
	}
	cout << endl;

	for(int y = 0; y != m_width; ++y) {
		//cout << y+1 << " ";
		printf("%2d", y+1);
		for(int x = 0; x != m_width; ++x) {
			auto ix = xyToIndex(x, y);
			//cout << (int)m_cells[ix] << " ";
			switch( m_cells[ix] ) {
#if 1
			case EMPTY: cout << "�E"; break;
			case BLACK: cout << "��"; break;
			case WHITE: cout << "��"; break;
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
		for(int x = 0; x != m_width; ++x) {
			auto ix = xyToIndex(x, y);
			cout << (int)m_gid[ix] << " ";
		}
		cout << endl;
	}
	cout << endl;
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
	m_cells[ix] = col;
	update_gid(ix, col);
	auto gid = m_gid[ix];
	if( col == BLACK ) {
		return find_horz(gid, 0) && find_horz(gid, m_width-1);		//	�㉺�ӂƘA���H
	} else {
		return find_vert(gid, 0) && find_vert(gid, m_width-1);		//	���E�ӂƘA���H
	}
}
void Board::saveState() {
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
	if (m_gid[ix] == 0)		// �ŏ��̘A���̏ꍇ
		m_gid[ix] = m_gid[ix2];
	else if( m_gid[ix] != m_gid[ix2] ) {		// �O���[�vid �̃}�[�W���K�v
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
