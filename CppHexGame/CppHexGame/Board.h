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

	int		xyToIndex(int x, int y) const {
		return (y+1)*m_ary_width + x;
	}
	void	print() const;
	void	put(int x, int y, uchar col);
public:
	int		m_width;
	int		m_ary_width;
	int		m_ary_height;
	int		m_ary_size;
	std::vector<uchar> m_cells;
};

