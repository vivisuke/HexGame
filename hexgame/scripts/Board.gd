class_name Board
extends Node

enum {
	EMPTY = 0, BLACK, WHITE,
}
const BD_SIZE = 8

var m_cells = []

func _init():
	m_cells.resize(BD_SIZE)

func _ready():
	pass # Replace with function body.
func _process(delta):
	pass
