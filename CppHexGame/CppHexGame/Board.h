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
	void	print_gid() const;
	bool	put(int x, int y, uchar col);		//	return: �I�ǂ����H
	void	update_gid(int ix, uchar col);
	void	update_gid_sub(int ix, int ix2);
public:
	int		m_width;
	int		m_ary_width;
	int		m_ary_height;
	int		m_ary_size;
	uchar	m_seq_gid;
	std::vector<uchar> m_cells;
	std::vector<uchar> m_gid;
};

