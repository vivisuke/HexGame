#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

Board::Board(int wd)
	: m_width(wd)
	, m_seq_gid(0)
{
	m_ary_width = m_width + 1;
	m_ary_height = m_width + 2;
	m_ary_size = m_ary_width * m_ary_height;
	m_cells.resize(m_ary_size);
	for(auto &v : m_cells) v = EMPTY;
	m_gid.resize(m_ary_size);
	for(auto &v : m_gid) v = 0;
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
		for(int x = 0; x != m_width; ++x) {
			auto ix = xyToIndex(x, y);
			cout << (int)m_gid[ix] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
bool Board::put(int x, int y, uchar col) {
	auto ix = xyToIndex(x, y);
	m_cells[ix] = col;
	update_gid(ix, col);
	return false;
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
