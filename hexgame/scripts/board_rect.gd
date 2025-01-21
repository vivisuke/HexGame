extends ColorRect

var CELL_WD = self.size.x / (Board.BD_SIZE+1)
var X0 = CELL_WD
var Y0 = CELL_WD
var GRID_WD = CELL_WD * (Board.BD_SIZE-1)
var GRID_HT = CELL_WD * (Board.BD_SIZE-1)

# Called when the node enters the scene tree for the first time.
func _ready():
	print("CELL_WD = ", CELL_WD)
	pass # Replace with function body.

func _draw():
	draw_rect(Rect2(X0, Y0, GRID_WD, GRID_HT), Color.BLACK, false, 3.0)
	for i in range(1, Board.BD_SIZE-1):
		var t = Y0 + i * CELL_WD
		draw_line(Vector2(X0, t), Vector2(X0+GRID_WD, t), Color.BLACK)
		draw_line(Vector2(t, Y0), Vector2(t, Y0+GRID_HT), Color.BLACK)
		draw_line(Vector2(X0, t), Vector2(t, Y0), Color.BLACK)
		draw_line(Vector2(t, Y0+GRID_HT), Vector2(X0+GRID_WD, t), Color.BLACK)
	draw_line(Vector2(X0, Y0+GRID_HT), Vector2(X0+GRID_WD, Y0), Color.BLACK)
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
