extends ColorRect

#const WHITE_COL = Color("pink")
const WHITE_COL = Color("#f00000")
const BLACK_COL = Color("#6060ff")
const N_HORZ = Board.N_HORZ
const N_VERT = Board.N_HORZ
var CELL_WD = self.size.x / (Board.N_HORZ+1)
var X0 = CELL_WD
var Y0 = CELL_WD
var GRID_WD = CELL_WD * (Board.N_HORZ-1)
var GRID_HT = CELL_WD * (Board.N_HORZ-1)

var bd

# Called when the node enters the scene tree for the first time.
func _ready():
	#print("CELL_WD = ", CELL_WD)
	pass # Replace with function body.

func xyToPos(x, y):
	return Vector2(X0+CELL_WD*x, Y0+CELL_WD*y+CELL_WD*x/2.0)
func draw_stone(x, y, b):
	#var col = Color("#6060ff") if b else Color("pink")
	var col = BLACK_COL if b else WHITE_COL
	draw_circle(xyToPos(x, y), CELL_WD*0.4, col)
	draw_circle(xyToPos(x, y), CELL_WD*0.4, Color.BLACK, false, 1.0, true)
func _draw():
	#draw_rect(Rect2(X0, Y0, GRID_WD, GRID_HT), Color.BLACK, false, 3.0)
	const BWD = Board.N_HORZ
	for i in range(1, BWD-1):
		var t = Y0 + i * CELL_WD
		draw_line(xyToPos(0, i), xyToPos(N_HORZ-1, i), Color.BLACK)
		draw_line(xyToPos(i, 0), xyToPos(i, N_VERT-1), Color.BLACK)
		draw_line(xyToPos(0, i), xyToPos(i, 0), Color.BLACK)
		draw_line(xyToPos(i, N_VERT-1), xyToPos(N_HORZ-1, i), Color.BLACK)
		#draw_line(Vector2(X0, t), Vector2(X0+GRID_WD, t), Color.BLACK)
		#draw_line(Vector2(t, Y0), Vector2(t, Y0+GRID_HT), Color.BLACK)
		#draw_line(Vector2(X0, t), Vector2(t, Y0), Color.BLACK)
		#draw_line(Vector2(t, Y0+GRID_HT), Vector2(X0+GRID_WD, t), Color.BLACK)
	draw_line(xyToPos(0, N_VERT-1), xyToPos(N_HORZ-1, 0), Color.BLACK)		# 主対角線
	#draw_line(Vector2(X0, Y0+GRID_HT), Vector2(X0+GRID_WD, Y0), Color.BLACK)		# 主対角線
	const FR_WD = 5.0
	draw_line(xyToPos(0, 0), xyToPos(N_HORZ-1, 0), BLACK_COL, FR_WD)
	draw_line(xyToPos(0, N_VERT-1), xyToPos(N_HORZ-1, N_VERT-1), BLACK_COL, FR_WD)
	draw_line(xyToPos(0, 0), xyToPos(0, N_VERT-1), WHITE_COL, FR_WD)
	draw_line(xyToPos(N_HORZ-1, 0), xyToPos(N_HORZ-1, N_VERT-1), WHITE_COL, FR_WD)
	#draw_stone(1, 0, true)
	#draw_stone(1, 1, true)
	#draw_stone(2, 0, false)
	#draw_stone(0, 2, false)
	for y in range(BWD):
		for x in range(BWD):
			var col = bd.get_col(x, y)
			if col != Board.EMPTY:
				draw_stone(x, y, col == Board.BLACK)
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
