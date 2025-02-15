#pragma once

#include <vector>

typedef unsigned char uchar;

class Board;

enum {
	EMPTY = 0, BLACK, WHITE, BWALL, WWALL,
};

struct MCTSNode {
	int		m_ix;		//	����ӏ�
	uchar	m_col;		//	���
	int		m_wins;		//	����
	int		m_visits;	//	�T����
	MCTSNode	*m_parent;					//	�e�m�[�h
	std::vector<MCTSNode>	m_children;		//	�q�m�[�h
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
	uchar		m_col;			//	root �ǖʂł̎��̎�ԁABLACK or WHITE
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
	bool	put(int x, int y, uchar col);		//	return: �I�ǂ����H
	bool	put(int ix, uchar col);				//	return: �I�ǂ����H
	void	saveState();						//	��ԕۑ��ifor Undo�j
	bool	saveStatePut(int ix, uchar col);	//	��ԕۑ��ifor Undo�j������֐�
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

