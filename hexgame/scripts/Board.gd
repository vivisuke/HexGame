class_name Board
extends Node

enum {
	EMPTY = 0, BLACK, WHITE, WALL
}
const N_HORZ = 8
const ARY_WIDTH = N_HORZ + 1
const ARY_HEIGHT = N_HORZ + 2
const ARY_SIZE = ARY_WIDTH * ARY_HEIGHT
#const col_str = ".XO#"
const col_str = ". X O # "
#const col_str = "・●◯＃"

#var m_cells = []
var m_cells : PackedByteArray
var m_visited : PackedByteArray		# 0 for 未探索 or 空欄、1以上 for 島id
var m_dist : PackedByteArray		# 0 for 未探索、1以上 for 距離+1
var m_ter_lst : PackedByteArray		# 末端位置リスト
var m_next_ter : PackedByteArray	# 次の末端位置リスト

func xyToIndex(x, y): return (y+1)*ARY_WIDTH + x

func _init():
	m_cells.resize(ARY_SIZE)
	m_cells.fill(WALL)
	m_visited.resize(ARY_SIZE)
	m_dist.resize(ARY_SIZE)
	for y in range(N_HORZ):
		for x in range(N_HORZ):
			m_cells[xyToIndex(x, y)] = EMPTY
func print():
	for y in range(N_HORZ):
		var txt = ""
		for x in range(N_HORZ):
			txt += col_str.substr(m_cells[xyToIndex(x, y)]*2, 2)
			#txt += "%d"%m_cells[xyToIndex(x, y)]
			#print(m_cells[i])
		print(txt)
func print_visited():
	for y in range(N_HORZ):
		var txt = ""
		for x in range(N_HORZ):
			txt += "%3d"%m_visited[xyToIndex(x, y)]
		print(txt)
func print_dist():
	for y in range(N_HORZ):
		var txt = ""
		for x in range(N_HORZ):
			txt += "%3d"%m_dist[xyToIndex(x, y)]
		print(txt)
func get_col(x, y):
	return m_cells[xyToIndex(x, y)]
func find_horz(id, y):
	for x in range(N_HORZ):
		if m_visited[xyToIndex(x, y)] == id:
			return true
	return false
func find_vert(id, x):
	for y in range(N_HORZ):
		if m_visited[xyToIndex(x, y)] == id:
			return true
	return false
func put_col(x, y, col) -> bool:
	var ix = xyToIndex(x, y)
	m_cells[ix] = col
	check_connected()
	var id = m_visited[ix]
	if col == BLACK:
		return find_horz(id, 0) && find_horz(id, N_HORZ-1)
	else:
		return find_vert(id, 0) && find_vert(id, N_HORZ-1)
func put_black(x, y):
	m_cells[xyToIndex(x, y)] = BLACK
func put_white(x, y):
	m_cells[xyToIndex(x, y)] = WHITE
func sel_move_random() -> Vector2:
	var lst : PackedVector2Array
	for y in range(N_HORZ):
		for x in range(N_HORZ):
			if m_cells[xyToIndex(x, y)] == EMPTY: lst.push_back(Vector2(x, y))
	print("lst.size = ", lst.size())
	if lst.size() != 0:
		return lst[randi() % lst.size()]
	else:
		return Vector2(-1, -1)
func check_connected_sub(ix, col, id):		# 深さ優先探索
	m_visited[ix] = id
	if m_cells[ix-ARY_WIDTH] == col && m_visited[ix-ARY_WIDTH] == 0:
		check_connected_sub(ix-ARY_WIDTH, col, id)
	if m_cells[ix-ARY_WIDTH+1] == col && m_visited[ix-ARY_WIDTH+1] == 0:
		check_connected_sub(ix-ARY_WIDTH+1, col, id)
	if m_cells[ix-1] == col && m_visited[ix-1] == 0:
		check_connected_sub(ix-1, col, id)
	if m_cells[ix+1] == col && m_visited[ix+1] == 0:
		check_connected_sub(ix+1, col, id)
	if m_cells[ix+ARY_WIDTH-1] == col && m_visited[ix+ARY_WIDTH-1] == 0:
		check_connected_sub(ix+ARY_WIDTH-1, col, id)
	if m_cells[ix+ARY_WIDTH] == col && m_visited[ix+ARY_WIDTH] == 0:
		check_connected_sub(ix+ARY_WIDTH, col, id)
func check_connected():
	m_visited.fill(0)
	var id = 0
	for y in range(N_HORZ):
		for x in range(N_HORZ):
			var ix = xyToIndex(x, y)
			var col = m_cells[ix]
			if (col == BLACK || col == WHITE) && m_visited[ix] == 0:
				id += 1
				check_connected_sub(ix, col, id)
func BFS_sub(dist, col):
	#m_next_ter.clear()
	m_next_ter = PackedByteArray()
	for ix in m_ter_lst:
		if m_cells[ix-ARY_WIDTH] == col && m_dist[ix-ARY_WIDTH] == 0:
			m_dist[ix-ARY_WIDTH] = dist
			m_next_ter.push_back(ix-ARY_WIDTH)
		if m_cells[ix-ARY_WIDTH+1] == col && m_dist[ix-ARY_WIDTH+1] == 0:
			m_dist[ix-ARY_WIDTH+1] = dist
			m_next_ter.push_back(ix-ARY_WIDTH+1)
		if m_cells[ix-1] == col && m_dist[ix-1] == 0:
			m_dist[ix-1] = dist
			m_next_ter.push_back(ix-1)
		if m_cells[ix+1] == col && m_dist[ix+1] == 0:
			m_dist[ix+1] = dist
			m_next_ter.push_back(ix+1)
		if m_cells[ix+ARY_WIDTH-1] == col && m_dist[ix+ARY_WIDTH-1] == 0:
			m_dist[ix+ARY_WIDTH-1] = dist
			m_next_ter.push_back(ix+ARY_WIDTH-1)
		if m_cells[ix+ARY_WIDTH] == col && m_dist[ix+ARY_WIDTH] == 0:
			m_dist[ix+ARY_WIDTH] = dist
			m_next_ter.push_back(ix+ARY_WIDTH)
	if m_next_ter.is_empty(): return
	m_ter_lst = m_next_ter.duplicate()
	BFS_sub(dist+1, col)

func BFS(x, y):		# (x, y) から幅優先探索
	m_dist.fill(0)
	var ix = xyToIndex(x, y)
	m_dist[ix] = 1
	var col = m_cells[ix]
	m_ter_lst = [ix]
	BFS_sub(2, col)

	pass
func _ready():
	pass # Replace with function body.
func _process(delta):
	pass
