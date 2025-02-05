extends Node2D

var bd
var next = Board.BLUE
var game_over = false
var move_hist : PackedVector3Array = []		# 着手履歴 for Undo、要素：(x, y, col)

func _ready():
	#seed(1)
	bd = Board.new()
	$BoardRect.bd = bd
	init_board()
	#bd.put_black(0, 1)
	#bd.put_white(1, 0)
	#bd.print()
	print_next()
	bd.print_gid()
	bd.eval_empty()
	bd.print_eval()
	if false:
		#for i in range(Board.N_HORZ * Board.N_HORZ):
		for i in range(64):
			var pos = bd.sel_move_random()
			print("put pos = ", pos)
			if bd.put_col(pos.x, pos.y, next):
				break
			next = (Board.BLUE + Board.RED) - next
		if next == Board.BLUE:
			$MessLabel.text = "青の勝ちです。"
		else:
			$MessLabel.text = "赤の勝ちです。"
		bd.print()
		bd.check_connected()
		bd.print_gid()
	pass # Replace with function body.
func init_board():
	game_over = false
	next = Board.BLUE
	move_hist.clear()
	bd.init()
	$BoardRect.queue_redraw()
func print_next():
	if next == Board.BLUE:
		$MessLabel.text = "青の手番です。"
	else:
		$MessLabel.text = "赤の手番です。"
func _process(delta):
	pass

func do_put(pos):
	move_hist.push_back(Vector3(pos.x, pos.y, next))
	$BoardRect.put_pos = pos
	$BoardRect.queue_redraw()
	if bd.put_col(pos.x, pos.y, next):
		# 終局した場合
		game_over = true
		if next == Board.BLUE:
			$MessLabel.text = "青の勝ちです。"
		else:
			$MessLabel.text = "赤の勝ちです。"
		bd.print()
		#bd.check_connected()
		bd.print_gid()
		bd.BFS(pos.x, pos.y)
		bd.print_dist()
		bd.get_shortest_path(next == Board.BLUE)
		$BoardRect.view_path = true
	else:
		#bd.print()
		bd.BFS(pos.x, pos.y)
		#bd.print_dist()
		next = (Board.BLUE + Board.RED) - next
		print_next()
		#bd.print_gid()
		bd.eval_empty()
		bd.print_eval()
func _input(event):
	if event is InputEventMouseButton && event.is_pressed():
		var pos = get_global_mouse_position() - $BoardRect.position
		print("pos = ", pos)
		var xy = $BoardRect.posToXY(pos)
		print("xy = ", xy)
		if xy.x >= 0 && xy.x < Board.N_HORZ && xy.y >= 0 && xy.y < Board.N_HORZ:
			if bd.get_col(xy.x, xy.y) == Board.EMPTY:
				do_put(xy)

func _on_next_button_pressed():
	if game_over: return
	var pos
	if next == Board.BLUE:
		#pos = bd.sel_move_random()
		#pos = bd.sel_move_PMC(next)
		pos = bd.sel_move_MCTS(next)
	else:
		#pos = bd.sel_move_PMC(next)
		pos = bd.sel_move_MCTS(next)
	#var pos = bd.sel_move_random()
	#var pos = bd.sel_move_maxeval()
	#var pos = bd.sel_move_PMC(next)
	#var pos = bd.sel_move_MCTS(next)
	$EvalLabel.text = "WR = %.1f%%" % (bd.win_rate*100)
	#var mcts = MCTS.new(bd, Board.BLUE, Board.RED)
	#mcts.add_children()
	#mcts.print()
	print("put pos = ", pos)
	do_put(pos)
	pass # Replace with function body.


func _on_restart_button_pressed():
	init_board()
	$BoardRect.init()
	pass # Replace with function body.


func _on_undo_button_pressed():
	if move_hist.is_empty(): return
	game_over = false
	next = Board.BLUE
	bd.init()
	move_hist.resize(move_hist.size() - 1)
	for pos in move_hist:
		bd.put_col(pos.x, pos.y, next)
		next = (Board.BLUE + Board.RED) - next
	$BoardRect.queue_redraw()
	pass # Replace with function body.
