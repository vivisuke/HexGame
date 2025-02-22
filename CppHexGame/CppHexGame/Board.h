#pragma once

#include <vector>

typedef unsigned char uchar;

class Board;

enum {
	EMPTY = 0, BLACK, WHITE, BWALL, WWALL,
};

void calc_softmax(const std::vector<int>& evList, std::vector<double>&);

struct MCTSNode {
	short	m_ix;		//	着手箇所
	uchar	m_col;		//	手番
	int		m_wins;		//	勝数
	int		m_sum_eval;	//	評価値合計
	int		m_visits;	//	探索数
	MCTSNode	*m_parent;					//	親ノード
	std::vector<MCTSNode>	m_children;		//	子ノード
public:
	MCTSNode(short ix = -1, uchar col = EMPTY)	//	col: 次の手番
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
	MCTSNode *select_child_ucb(double = 1.4);		//	引数値が大きいほど、低評価ノード探索：高確率
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
	int		ixToX(int ix ) const { return ix % m_ary_width; }
	int		ixToY(int ix ) const { return ix / m_ary_width - 1; }
	int		n_empty() const;
	void	print() const;
	void	print_gid() const;
	void	print_put_stack() const;
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
	int		sel_move_MCTS_ev() const;			//	末端評価値によるモンテカルロ木探索
	uchar	rollout(int ix, uchar col);
	int		rollout(int ix, uchar col, int n_empty);		//	評価値を返す
	int		min_max(uchar col, int n_empty);	//	黒から見た評価値を返す（(勝：+1, 負：-1) ±空欄数）
	int		min_level(int n_empty);				//	黒から見た評価値を返す（(勝：+1, 負：-1) ±空欄数）
	int		max_level(int n_empty);				//	黒から見た評価値を返す（(勝：+1, 負：-1) ±空欄数）
	int		min_level(int alpha, int beta, int n_empty);	//	黒から見た評価値を返す（(勝：+1, 負：-1) ±空欄数）
	int		max_level(int alpha, int beta, int n_empty);	//	黒から見た評価値を返す（(勝：+1, 負：-1) ±空欄数）
	int		alpha_beta(uchar);
public:
	int		m_width;
	int		m_ary_width;
	int		m_ary_height;
	int		m_ary_size;
	uchar	m_seq_gid;
	__int64		m_n_node;					//	末端ノード数
	std::vector<uchar> m_cells;
	std::vector<uchar> m_gid;
	std::vector<uchar> m_gid_stack;
	std::vector<int> m_put_stack;		//	着手箇所
	std::vector<int> m_seq_stack;		//	for m_seq_gid
};

