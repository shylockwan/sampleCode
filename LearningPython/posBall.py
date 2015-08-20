import SimpleGUICS2Pygame.simpleguics2pygame as simplegui
import random
WIDTH=600
HEIGHT=400
position=[WIDTH/2,HEIGHT/2]
value=0
vel=[0,0]
def input_handle(text):
	global value
	value=float(text)
def draw(canvas):
	canvas.draw_circle(position,10,10,"Red")
def keydown(key):
	delta=5
	if key == simplegui.KEY_MAP['left']:
		position[0]-=delta
	elif key == simplegui.KEY_MAP["right"]:
		position[0]+=delta
	elif key == simplegui.KEY_MAP["down"]:
		position[1]+=delta
	elif key == simplegui.KEY_MAP["up"]:
		position[1]-=delta
frame=simplegui.create_frame("test",WIDTH,HEIGHT)
frame.set_draw_handler(draw)
frame.add_input("Enter Value",input_handle,100)
frame.set_keydown_handler(keydown)
#timer=simplegui.create_timer(1000,timer_handle)
#timer.start()
frame.start()
