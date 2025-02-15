#pragma once

#include <vector>

typedef unsigned char uchar;

class Board;

enum {
	EMPTY = 0, BLACK, WHITE, BWALL, WWALL,
};

struct MCTSNode {
	int		m_ix;		//	着手箇所
	uchar	m_col;		//	手番
	int		m_wins;		//	勝数
	int		m_visits;	//	探索数
	MCTSNode	*m_parent;					//	親ノード
	std::vector<MCTSNode>	m_children;		//	子ノード
public:
	MCTSNode(int ix = -1, uchar col = EMPTY)
		: m_ix(ix), m_col(col)
		, m_parent(NULL)
	{
		m_wins = m_visits = 0;
	}
	~MCTSNode() {
		//for(auto *ptr : m_children) free(ptr);
	}
	double calculate_ucb(double = 2.0) const;
	MCTSNode *select_child_ucb(double = 2.0);
};
class MCTS {
public:
	MCTS(const Board*, uchar col=BLACK);
	~MCTS() {
		//free(m_root);
	}
public:
	void	do_expand(MCTSNode*);
	void	do_search(int itr = 10000);
public:
	const Board* m_board;
	uchar		m_col;			//	root 局面での次の手番、BLACK or WHITE
	MCTSNode	m_root;
};


class Board
{
public:
	Board(int wd = 11);
	void	init();
	int		xyToIndex(int x, int y) const {
		return (y+1)*m_ary_width + x;
	}
	int		n_empty() const;
	void	print() const;
	void	print_gid() const;
	void	copy_from(const Board&);
	bool	put(int x, int y, uchar col);		//	return: 終局した？
	bool	put(int ix, uchar col);				//	return: 終局した？
	void	saveState();						//	状態保存（for Undo）
	bool	saveStatePut(int ix, uchar col);	//	状態保存（for Undo）＆着手関数
	bool	saveStatePut(int x, int y, uchar col) { return saveStatePut(xyToIndex(x, y), col); }
	void	undo(int ix);
	void	undo(int x, int y) { undo(xyToIndex(x, y)); }
	void	update_gid(int ix, uchar col);
	void	update_gid_sub(int ix, int ix2);
	bool	find_horz(uchar id, int y);
	bool	find_vert(uchar id, int x);
	int		sel_move_random() const;
	uchar	rollout(int ix, uchar col);
public:
	int		m_width;
	int		m_ary_width;
	int		m_ary_height;
	int		m_ary_size;
	uchar	m_seq_gid;
	std::vector<uchar> m_cells;
	std::vector<uchar> m_gid;
	std::vector<uchar> m_gid_stack;
};

