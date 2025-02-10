#include <iostream>
#include <string>
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
const char *wstr[] = {"ÇÅ", "ÇÇ", "ÇÉ", "ÇÑ", "ÇÖ", "ÇÜ", "Çá", "Çà", "Çâ", "Çä", "Çã"};
void Board::print() const {
	cout << "  ";
	for(int x = 0; x != m_width; ++x) {
		cout << wstr[x];
		//wcout << wstring(1, ('ÇÅ' + x));
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
			case EMPTY: cout << "ÅE"; break;
			case BLACK: cout << "Åú"; break;
			case WHITE: cout << "Å¸"; break;
#else
			case EMPTY: cout << ". "; break;
			case BLACK: cout << "X "; break;
			case WHITE: cout << "O "; break;
#endif
			}
		}
		cout << endl;
	}
}
void Board::put(int x, int y, uchar col) {
	auto ix = xyToIndex(x, y);
	m_cells[ix] = col;
}
