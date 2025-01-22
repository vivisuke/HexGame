extends Node2D

var bd

func _ready():
	bd = Board.new()
	$BoardRect.bd = bd
	bd.put_black(0, 1)
	bd.put_white(1, 0)
	bd.print()
	pass # Replace with function body.
	
func _process(delta):
	pass
