#pragma once

#include <vector>

typedef unsigned char uchar;

class Board;

enum {
	EMPTY = 0, BLACK, WHITE, BWALL, WWALL,
};

void calc_softmax(const std::vector<int>& evList, std::vector<double>&);

struct MCTSNode {
	short	m_ix;		//	����ӏ�
	uchar	m_col;		//	���
	int		m_wins;		//	����
	int		m_sum_eval;	//	�]���l���v
	int		m_visits;	//	�T����
	MCTSNode	*m_parent;					//	�e�m�[�h
	std::vector<MCTSNode>	m_children;		//	�q�m�[�h
public:
	MCTSNode(short ix = -1, uchar col = EMPTY)	//	col: ���̎��
		: m_ix(ix), m_col(col)
		, m_parent(NULL)
	{
		m_wins = m_visits = 0;
		m_sum_eval = 0;
	}
	~MCTSNode() {
		//for(auto *ptr : m_children) free(ptr);
	}
	void print(int depth = 0) const;
	double calculate_ucb(double = 2.0) const;
	MCTSNode *select_child_ucb(double = 1.4);		//	�����l���傫���قǁA��]���m�[�h�T���F���m��
};
class MCTS {
public:
	MCTS(const Board*, uchar col=BLACK);
	~MCTS() {
		//free(m_root);
	}
public:
	void	print() const;
	void	do_expand(MCTSNode*);
	void	do_backpropagation(MCTSNode*, int);
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
	int		ixToX(int ix ) const { return ix % m_ary_width; }
	int		ixToY(int ix ) const { return ix / m_ary_width - 1; }
	int		n_empty() const;
	void	print() const;
	void	print_gid() const;
	void	print_put_stack() const;
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
	int		sel_move_MCTS_ev() const;			//	���[�]���l�ɂ�郂���e�J�����ؒT��
	uchar	rollout(int ix, uchar col);
	int		rollout(int ix, uchar col, int n_empty);		//	�]���l��Ԃ�
	int		min_max(uchar col, int n_empty);	//	�����猩���]���l��Ԃ��i(���F+1, ���F-1) �}�󗓐��j
	int		min_level(int n_empty);				//	�����猩���]���l��Ԃ��i(���F+1, ���F-1) �}�󗓐��j
	int		max_level(int n_empty);				//	�����猩���]���l��Ԃ��i(���F+1, ���F-1) �}�󗓐��j
	int		min_level(int alpha, int beta, int n_empty);	//	�����猩���]���l��Ԃ��i(���F+1, ���F-1) �}�󗓐��j
	int		max_level(int alpha, int beta, int n_empty);	//	�����猩���]���l��Ԃ��i(���F+1, ���F-1) �}�󗓐��j
	int		alpha_beta(uchar);
public:
	int		m_width;
	int		m_ary_width;
	int		m_ary_height;
	int		m_ary_size;
	uchar	m_seq_gid;
	__int64		m_n_node;					//	���[�m�[�h��
	std::vector<uchar> m_cells;
	std::vector<uchar> m_gid;
	std::vector<uchar> m_gid_stack;
	std::vector<int> m_put_stack;		//	����ӏ�
	std::vector<int> m_seq_stack;		//	for m_seq_gid
};

