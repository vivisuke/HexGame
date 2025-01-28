class_name MCTS
extends Node

class MCTSNode:
	var board_state		# 盤面状態 (Grid クラスのインスタンスなど)
	var parent = null	# 親ノード (MCTSNode)
	var children = []	# 子ノード (MCTSNode の配列)
	var visits = 0		# 訪問回数
	var wins = 0		# 勝利回数 (ロールアウトで勝利した場合にカウント)
	var prior_probability = 0.0		# 事前確率 (必要に応じて使用)
	var move : Vector2i
	
	func _init(board_state, parent_node, move_made):
		pass

var root_node: MCTSNode
var board_size: int
var player_color: int # MCTSで探索するプレイヤーの色
var opponent_color: int
#var heuristic_calculator: HexHeuristicValueCalculator # ヒューリスティック計算クラス

var c_puct = 1.5 # UCB の探索パラメータ (調整可能)
var rollout_depth_limit = 50 # ロールアウトの深さ制限 (無限ループ対策)

func _init(board: Board, p_color: int, o_color: int):
	board_size = board.N_HORZ
	player_color = p_color
	opponent_color = o_color
	root_node = MCTSNode.new(board.duplicate(), null, null) # 初期盤面を根ノードとする
	#heuristic_calculator = HexHeuristicValueCalculator.new(board_size)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
