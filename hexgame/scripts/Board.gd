class_name Board
extends Node

enum {
	EMPTY = 0, BLACK, WHITE,
}
const BD_SIZE = 8

var m_cells = []

func _init():
	m_cells.resize(BD_SIZE)
	for i in range(BD_SIZE):
		m_cells[i] = []
		m_cells[i].resize(BD_SIZE)
		m_cells[i].fill(EMPTY)
func print():
	for i in range(BD_SIZE):
		print(m_cells[i])
func put_black(x, y):
	m_cells[y][x] = BLACK
func put_white(x, y):
	m_cells[y][x] = WHITE
func _ready():
	pass # Replace with function body.
func _process(delta):
	pass
