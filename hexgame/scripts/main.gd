extends Node2D

var bd

func _ready():
	#seed(1)
	bd = Board.new()
	$BoardRect.bd = bd
	#bd.put_black(0, 1)
	#bd.put_white(1, 0)
	#bd.print()
	var next = Board.BLACK
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
	
func _process(delta):
	pass
