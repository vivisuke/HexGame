#include <iostream>
#include <string>
#include <random>
#include "Board.h"

using namespace std;

std::mt19937 rgen(std::random_device{}()); // V[hðÝè

Board::Board(int wd)
	: m_width(wd)
{
	m_ary_width = m_width + 1;
	m_ary_height = m_width + 2;
	m_ary_size = m_ary_width * m_ary_height;
	m_cells.resize(m_ary_size);
	m_gid.resize(m_ary_size);
	init();
}
void Board::init() {
	m_seq_gid = 0;
	for(auto &v : m_cells) v = EMPTY;
	for(auto &v : m_gid) v = 0;
}
const char *wstr[] = {"", "", "", "", "", "", "", "", "", "", ""};
void Board::print() const {
	cout << "  ";
	for(int x = 0; x != m_width; ++x) {
		cout << wstr[x];
		//wcout << wstring(1, ('' + x));
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
			case EMPTY: cout << "E"; break;
			case BLACK: cout << ""; break;
			case WHITE: cout << "ü"; break;
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
		return find_horz(gid, 0) && find_horz(gid, m_width-1);		//	ãºÓÆAH
	} else {
		return find_vert(gid, 0) && find_vert(gid, m_width-1);		//	¶EÓÆAH
	}
}
void Board::update_gid_sub(int ix, int ix2) {
	if( m_cells[ix2] != m_cells[ix] ) return;
	if (m_gid[ix] == 0)		// ÅÌAÌê
		m_gid[ix] = m_gid[ix2];
	else if( m_gid[ix] != m_gid[ix2] ) {		// O[vid Ì}[WªKv
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
