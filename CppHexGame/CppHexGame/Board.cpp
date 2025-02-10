#include <iostream>
#include "Board.h"

using namespace std;

Board::Board(int wd)
	: m_width(wd)
{
	m_ary_width = m_width + 1;
	m_ary_height = m_width + 2;
	m_ary_size = m_ary_width * m_ary_height;
	m_cells.resize(m_ary_size);
	for(auto &v : m_cells) v = EMPTY;
}
void Board::print() const {
	cout << "   ";
	for(int x = 0; x != m_width; ++x) cout << (char)('a'+x) << " ";
	cout << endl;

	for(int y = 0; y != m_width; ++y) {
		//cout << y+1 << " ";
		printf("%2d ", y+1);
		for(int x = 0; x != m_width; ++x) {
			auto ix = xyToIndex(x, y);
			//cout << (int)m_cells[ix] << " ";
			switch( m_cells[ix] ) {
			case EMPTY: cout << ". "; break;
			case BLACK: cout << "X "; break;
			case WHITE: cout << "O "; break;
			}
		}
		cout << endl;
	}
}
