class_name Board
extends Node

enum {
	EMPTY = 0, BLACK, WHITE, WALL
}
const BD_WIDTH = 8
const ARY_WIDTH = BD_WIDTH + 1
const ARY_HEIGHT = BD_WIDTH + 2
const ARY_SIZE = ARY_WIDTH * ARY_HEIGHT
#const col_str = ".XO#"
const col_str = ". X O # "
#const col_str = "・●◯＃"

#var m_cells = []
var m_cells : PackedByteArray

func xyToIndex(x, y): return (y+1)*ARY_WIDTH + x

func _init():
	m_cells.resize(ARY_SIZE)
	m_cells.fill(WALL)
	for y in range(BD_WIDTH):
		for x in range(BD_WIDTH):
			m_cells[xyToIndex(x, y)] = EMPTY
func print():
	for y in range(BD_WIDTH):
		var txt = ""
		for x in range(BD_WIDTH):
			txt += col_str.substr(m_cells[xyToIndex(x, y)]*2, 2)
			#txt += "%d"%m_cells[xyToIndex(x, y)]
			#print(m_cells[i])
		print(txt)
func get_col(x, y):
	return m_cells[xyToIndex(x, y)]
func put_col(x, y, col):
	m_cells[xyToIndex(x, y)] = col
func put_black(x, y):
	m_cells[xyToIndex(x, y)] = BLACK
func put_white(x, y):
	m_cells[xyToIndex(x, y)] = WHITE
func sel_move_random() -> Vector2:
	var lst : PackedVector2Array
	for y in range(BD_WIDTH):
		for x in range(BD_WIDTH):
			if m_cells[xyToIndex(x, y)] == EMPTY: lst.push_back(Vector2(x, y))
	print("lst.size = ", lst.size())
	if lst.size() != 0:
		return lst[randi() % lst.size()]
	else:
		return Vector2(-1, -1)
func _ready():
	pass # Replace with function body.
func _process(delta):
	pass
