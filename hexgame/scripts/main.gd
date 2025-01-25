extends Node2D

var bd
var next = Board.BLACK
var game_over = false

func _ready():
	#seed(1)
	bd = Board.new()
	$BoardRect.bd = bd
	#bd.put_black(0, 1)
	#bd.put_white(1, 0)
	#bd.print()
	#var next = Board.BLACK
	print_next()
	bd.eval_empty()
	bd.print_eval()
	if false:
		#for i in range(Board.N_HORZ * Board.N_HORZ):
		for i in range(64):
			var pos = bd.sel_move_random()
			print("put pos = ", pos)
			if bd.put_col(pos.x, pos.y, next):
				break
			next = (Board.BLACK + Board.WHITE) - next
		if next == Board.BLACK:
			$MessLabel.text = "青の勝ちです。"
		else:
			$MessLabel.text = "赤の勝ちです。"
		bd.print()
		bd.check_connected()
		bd.print_visited()
	pass # Replace with function body.
func print_next():
	if next == Board.BLACK:
		$MessLabel.text = "青の手番です。"
	else:
		$MessLabel.text = "赤の手番です。"
func _process(delta):
	pass

func do_put(pos):
	$BoardRect.put_pos = pos
	$BoardRect.queue_redraw()
	if bd.put_col(pos.x, pos.y, next):
		game_over = true
		if next == Board.BLACK:
			$MessLabel.text = "青の勝ちです。"
		else:
			$MessLabel.text = "赤の勝ちです。"
		bd.print()
		#bd.check_connected()
		#bd.print_visited()
		bd.BFS(pos.x, pos.y)
		bd.print_dist()
		bd.get_shortest_path(next == Board.BLACK)
		$BoardRect.view_path = true
	else:
		bd.BFS(pos.x, pos.y)
		bd.print_dist()
		next = (Board.BLACK + Board.WHITE) - next
		print_next()
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
	var pos = bd.sel_move_random()
	print("put pos = ", pos)
	do_put(pos)
	pass # Replace with function body.
