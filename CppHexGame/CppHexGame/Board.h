#pragma once

#include <vector>

typedef unsigned char uchar;

//const int N_HORZ = 3;

enum {
	EMPTY = 0, BLACK, WHITE, BWALL, WALL,
};

class Board
{
public:
	Board(int wd = 11);
public:
	int		m_width;
	int		m_ary_width;
	int		m_ary_height;
	int		m_ary_size;
	std::vector<uchar> m_cells;
};

